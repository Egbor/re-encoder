#include "encoder.h"
#include "common/error.h"

#include <libavutil/opt.h>
#include <libavutil/avassert.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>

#include <stdio.h>

typedef struct _encoder_context {
  AVFormatContext* format_context;
  
  union {
    AVCodecContext* codec_context_table[2];
    struct {
      AVCodecContext* video_codec_context;
      AVCodecContext* audio_codec_context;
    };
  } media_context;
} encoder_context_t;

int samples_count = 0;

const enum AVCodecID avcodec_id_table[] = {
  AV_CODEC_ID_H264,
  AV_CODEC_ID_AC3,
};

#define ENCODER_MEDIA_CONTEXT_TYPE_VIDEO ((int)AVMEDIA_TYPE_VIDEO)
#define ENCODER_MEDIA_CONTEXT_TYPE_AUDIO ((int)AVMEDIA_TYPE_AUDIO)

void allocate_encoder_context(encoder_context_t** encoder_context) {
  encoder_context_t* context = (encoder_context_t*)malloc(sizeof(encoder_context_t));
  *encoder_context = context;
}

void open_encoder_format_context(encoder_context_t* encoder_context, const char* filename) {
  avformat_alloc_output_context2(&encoder_context->format_context, NULL, NULL, filename);
  if (!encoder_context->format_context) {
    throw_error("Encoder format context could not open.", -1);
  }
}

void open_encoder_codec_context(encoder_context_t* encoder_context, int media_type) {
  int status = 0;
  AVCodec* codec = NULL;
  AVStream* stream = NULL;
  AVCodecContext* codec_context = NULL;
  
  codec = avcodec_find_encoder(avcodec_id_table[media_type]);
  if (!codec) {
    throw_error("Encoder's video/audio codec could not found for this media file.", -1);
  }

  stream = avformat_new_stream(encoder_context->format_context, NULL);
  if (!stream) {
    throw_error("Encoder's video/audio stream could not create.", -1);
  }

  codec_context = avcodec_alloc_context3(codec);
  if (!codec_context) {
    throw_error("Decoder's video/audio codec context allocation failed.", -1);
  }

  stream->id = encoder_context->format_context->nb_streams-1;
  if (media_type == ENCODER_MEDIA_CONTEXT_TYPE_VIDEO) {
    codec_context->codec_id = avcodec_id_table[media_type];
    codec_context->bit_rate = 1153000;
    codec_context->width = 360;
    codec_context->height = 200;
    codec_context->time_base = (AVRational){1001, 24000};
    codec_context->framerate = (AVRational){24000, 1001};
    codec_context->gop_size = 1;
    codec_context->pix_fmt = AV_PIX_FMT_YUV420P;

    stream->start_time = -7;
    stream->time_base = (AVRational){1, 1000};
    stream->r_frame_rate = codec_context->framerate;
    stream->avg_frame_rate = codec_context->framerate;
    av_opt_set(codec_context->priv_data, "preset", "slow", 0);
    
  } else if (media_type == ENCODER_MEDIA_CONTEXT_TYPE_AUDIO) {
    codec_context->bit_rate = 384000;
    codec_context->sample_fmt = AV_SAMPLE_FMT_FLTP;
    codec_context->sample_rate = 48000;
    codec_context->channel_layout = AV_CH_LAYOUT_STEREO;
    codec_context->channels = av_get_channel_layout_nb_channels(codec_context->channel_layout);
  }

  if (encoder_context->format_context->oformat->flags & AVFMT_GLOBALHEADER)
    codec_context->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
  
  status = avcodec_open2(codec_context, codec, NULL);
  if (status < 0) {
    avcodec_free_context(&codec_context);
    throw_error("Could not open video/audio codec context to encoding.", status);
  }

  status = avcodec_parameters_from_context(stream->codecpar, codec_context);
  if (status < 0) {
    throw_error("Failed to copy codec parameters to codec context.", status);
  }

  encoder_context->media_context.codec_context_table[media_type] = codec_context;
}

void open_encoder_output_file(encoder_context_t* context, const char* filename) {
  int status = 0;
  AVOutputFormat* outformat = context->format_context->oformat;

  av_dump_format(context->format_context, 0, filename, 1);
  
  if (!(outformat->flags & AVFMT_NOFILE)) {
    status = avio_open(&context->format_context->pb, filename, AVIO_FLAG_WRITE);
    if (status < 0) {
      throw_error("Could not open output file.", status);
    }
  }
  
  status = avformat_write_header(context->format_context, NULL);
  if (status < 0) {
    throw_error(av_err2str(status), status);
  }
}

void encoder_open(encoder_context_t** encoder_context, const char* filename) {
  allocate_encoder_context(encoder_context);
  open_encoder_format_context(*encoder_context, filename);

  open_encoder_codec_context(*encoder_context, ENCODER_MEDIA_CONTEXT_TYPE_VIDEO);
  open_encoder_codec_context(*encoder_context, ENCODER_MEDIA_CONTEXT_TYPE_AUDIO);

  open_encoder_output_file(*encoder_context, filename);
}

void encoder_close(encoder_context_t** encoder_context) {
  encoder_context_t* context = *encoder_context;

  av_write_trailer(context->format_context);
  
  avcodec_free_context(&context->media_context.video_codec_context);
  avcodec_free_context(&context->media_context.audio_codec_context);
  avformat_free_context(context->format_context);
  free(context);

  context = NULL;
}

void encode_frame(encoder_context_t* encoder_context, frame_t* frame) {
  int status = 0;
  struct frame_item* item = frame_get_item(frame);

  AVFrame* avframe = (AVFrame*)item->buffer;
  AVStream* avstream = encoder_context->format_context->streams[item->stream_id];
  AVCodecContext* codec_context = encoder_context->media_context.codec_context_table[item->stream_id];

  AVPacket* avpacket = av_packet_alloc();
  if (!avpacket) {
    throw_error("Packet allocation failed.", -1);
  }

  status = avcodec_send_frame(codec_context, avframe);
  if (status < 0) {
    throw_error("Error sending a frame for encoding.", status);
  }

  while (status >= 0) {
    status = avcodec_receive_packet(codec_context, avpacket);
    if (status == AVERROR(EAGAIN) || status == AVERROR_EOF) {
      return;
    } else if (status < 0) {
      throw_error("Error during encoding.", status);
    }

    av_packet_rescale_ts(avpacket, codec_context->time_base, avstream->time_base);
    avpacket->stream_index = item->stream_id;

    status = av_interleaved_write_frame(encoder_context->format_context, avpacket);
    if (status < 0) {
      throw_error("Error during writting to file.", status);
    }

    av_packet_unref(avpacket);
  }
}

void encoder_set_frames(encoder_context_t* encoder_context, frame_t* video_frame, frame_t* audio_frame){
  AVCodecContext* video_codec_context = encoder_context->media_context.video_codec_context;
  AVCodecContext* audio_codec_context = encoder_context->media_context.audio_codec_context;
  
  while (video_frame || audio_frame) {
    AVFrame* video_avframe = NULL;
    AVFrame* audio_avframe = NULL;

    if (video_frame) {
      struct frame_item* video_item = frame_get_item(video_frame);
      video_avframe = (AVFrame*)video_item->buffer;
    }

    if (audio_frame) {
      struct frame_item* audio_item = frame_get_item(audio_frame);
      audio_avframe = (AVFrame*)audio_item->buffer;
    }
    
    if (video_frame &&
	(!audio_frame || av_compare_ts(video_avframe->pts, video_codec_context->time_base,
				       audio_avframe->pts, audio_codec_context->time_base) <= 0)) {
      encode_frame(encoder_context, video_frame);
      video_frame = frame_next(video_frame);
    } else {
      encode_frame(encoder_context, audio_frame);
      audio_frame = frame_next(audio_frame);
    }
  }
}

void* encoder_get_codec_context(encoder_context_t* encoder_context, int media_type) {
  return encoder_context->media_context.codec_context_table[media_type];
}
