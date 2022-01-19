#include "decoder.h"
#include "common/error.h"

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

#include <stdio.h>

struct timestamp {
  int64_t start;
  int64_t end;
};

typedef struct _decoder_context {
  AVFormatContext* format_context;
  
  union {
    AVCodecContext* codec_context_table[2];
    struct {
      AVCodecContext* video_codec_context;
      AVCodecContext* audio_codec_context;
    };
  } media_context;

  union {
    int stream_id_table[2];
    struct {
      int video_stream_id;
      int audio_stream_id;
    };
  } media_stream;

  union {
    struct timestamp timestamp_table[2];
    struct {
      struct timestamp video_timestamp;
      struct timestamp audio_timestamp;
    };
  } media_timestamp;
} decoder_context_t;

#define DECODER_MEDIA_CONTEXT_TYPE_VIDEO ((int)AVMEDIA_TYPE_VIDEO)
#define DECODER_MEDIA_CONTEXT_TYPE_AUDIO ((int)AVMEDIA_TYPE_AUDIO)

void allocate_decoder_context(decoder_context_t** decoder_context) {
  decoder_context_t* context = (decoder_context_t*)malloc(sizeof(decoder_context_t));
  
  context->format_context = avformat_alloc_context();
  if (!context->format_context) {
    throw_error("Decoder format context could not allocate.", -1);
  }
  
  *decoder_context = context;
}

void open_decoder_format_context(decoder_context_t* decoder_context, const char* filename) {
  int status = avformat_open_input(&decoder_context->format_context, filename, NULL, NULL);
  if (status < 0) {
  	throw_error(/*"Could not open source file"*/av_err2str(status), status);
  }
}

void open_decoder_codec_context(decoder_context_t* decoder_context, int media_type) {
  int status = 0;
  AVCodec* codec = NULL;
  AVCodecContext* codec_context = NULL;
  
  int stream = av_find_best_stream(decoder_context->format_context, media_type, -1, -1, &codec, 0);
  if (stream < 0) {
    throw_error("Decoder's video/audio codec could found for this media file.", stream);
  }
  
  codec_context = avcodec_alloc_context3(codec);
  if (!codec_context) {
    throw_error("Decoder's video/audio codec context allocation failed.", -1);
  }

  status = avcodec_parameters_to_context(codec_context,
					 decoder_context->format_context->streams[stream]->codecpar);
  if (status < 0) {
    throw_error("Failed to copy codec parameters to codec context.", status);
  }
  
  status = avcodec_open2(codec_context, codec, NULL);
  if (status < 0) {
    avcodec_free_context(&codec_context);
    throw_error("Could not open video/audio codec context to decoding.", status);
  }
  
  decoder_context->media_context.codec_context_table[media_type] = codec_context;
  decoder_context->media_stream.stream_id_table[media_type] = stream;
}

AVCodecContext* find_decoder_codec_context_by_stream_index(decoder_context_t* decoder_context,
							   int stream_index) {
  int stream_table_index = -1;
  for (int i = 0; i < 2; i++) {
    if (stream_index == decoder_context->media_stream.stream_id_table[i]) {
      stream_table_index = i;
      break;
    }
  }

  if (stream_table_index < 0) {
    throw_error("Underfined decoder stream index.", -1);
  }

  return decoder_context->media_context.codec_context_table[stream_table_index];
}

enum frame_type find_decoder_frame_type_by_stream_index(decoder_context_t* decoder_context,
							int stream_index) {
  for (int i = 0; i < 2; i++) {
    if (stream_index == decoder_context->media_stream.stream_id_table[i]) {
      return i;
    }
  }

  throw_error("Underfined decoder stream index.", -1);
}

void seek_decoder_timestamp(decoder_context_t* decoder_context, float start_ts, float end_ts,
			    int media_type) {
  int status = 0;
  AVStream* avstream = decoder_context->format_context->streams[media_type];
  
  uint64_t start_timestamp = av_rescale_q((int64_t)(start_ts * AV_TIME_BASE),
					  (AVRational){1, AV_TIME_BASE}, avstream->time_base);
  uint64_t end_timestamp = av_rescale_q((int64_t)(end_ts * AV_TIME_BASE),
					(AVRational){1, AV_TIME_BASE}, avstream->time_base);

  status = avformat_seek_file(decoder_context->format_context, avstream->index, INT64_MIN,
  			      start_timestamp, INT64_MAX, 0);
  if (status < 0) {
    throw_error("Error seeking a frame.", status);
  }

  decoder_context->media_timestamp.timestamp_table[media_type].start = start_timestamp;
  decoder_context->media_timestamp.timestamp_table[media_type].end = end_timestamp;
}

void set_decoder_timestamp(decoder_context_t* decoder_context, float start_ts, float end_ts) {
  if (start_ts > end_ts) {
    throw_error("Start timestamp < end timestamp.", -1);
  }
  
  seek_decoder_timestamp(decoder_context, start_ts, end_ts, DECODER_MEDIA_CONTEXT_TYPE_VIDEO);
  seek_decoder_timestamp(decoder_context, start_ts, end_ts, DECODER_MEDIA_CONTEXT_TYPE_AUDIO);
}

int check_frame_timestamp(decoder_context_t* decoder_context, AVFrame* frame, int media_type) {
  int64_t start_timestamp = decoder_context->media_timestamp.timestamp_table[media_type].start;
  int64_t end_timestamp = decoder_context->media_timestamp.timestamp_table[media_type].end;

  if (frame->pts >= start_timestamp && frame->pts <= end_timestamp) {
    frame->pts -= start_timestamp;
    return 1;
  }
  return 0;
}

void decoder_open(decoder_context_t** decoder_context, const char* filename, float start_ts,
		  float end_ts) {
  allocate_decoder_context(decoder_context);
  open_decoder_format_context(*decoder_context, filename);

  open_decoder_codec_context(*decoder_context, DECODER_MEDIA_CONTEXT_TYPE_VIDEO);
  open_decoder_codec_context(*decoder_context, DECODER_MEDIA_CONTEXT_TYPE_AUDIO);

  set_decoder_timestamp(*decoder_context, start_ts, end_ts);
}

void decoder_close(decoder_context_t** decoder_context) {
  decoder_context_t* context = *decoder_context;

  avcodec_free_context(&context->media_context.video_codec_context);
  avcodec_free_context(&context->media_context.audio_codec_context);
  avformat_close_input(&context->format_context);
  free(context);

  context = NULL;
}

frame_t* decoder_next_frame(decoder_context_t* decoder_context) {
  int status = 0;
  AVPacket* next_avpacket = av_packet_alloc();
  
  if (!next_avpacket) {
    throw_error("Packet allocation failed.", -1);
  }

  status = av_read_frame(decoder_context->format_context, next_avpacket);
  if (status < 0) {
    return NULL; // It's mean error or end of file
  }

  AVCodecContext* codec_context = find_decoder_codec_context_by_stream_index(decoder_context,
									     next_avpacket->stream_index);
  enum frame_type frame_type = find_decoder_frame_type_by_stream_index(decoder_context,
								       next_avpacket->stream_index);

  if (frame_type == 1) {
    codec_context->pkt_timebase = (AVRational){1, codec_context->sample_rate};
  }
  
  status = avcodec_send_packet(codec_context, next_avpacket);
  if (status < 0) {
    throw_error("Error sunbmitting the packet to the decoder.", status);
  }

  frame_t* frame_start = frame_alloc(frame_type);
  frame_t* frame_end = frame_start;

  while (status >= 0) {
    struct frame_item* item = frame_get_item(frame_end);
    item->stream_id = next_avpacket->stream_index;
    
    status = avcodec_receive_frame(codec_context, item->buffer);
    if (status == AVERROR(EAGAIN) || status == AVERROR_EOF) {
      frame_free(&frame_end);
      break;
    } else if (status < 0) {
      throw_error("Error during decoding.", status);
    }

    if (!check_frame_timestamp(decoder_context, item->buffer, item->stream_id)) {
      item->stream_id = -1;
      break;
    }

    frame_end = frame_alloc(frame_type);
    frame_attach_to(frame_start, frame_end);
  }
  
  return frame_start;
}
