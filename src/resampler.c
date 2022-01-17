#include "resampler.h"
#include "common/error.h"

#include <libavcodec/avcodec.h>

#include <stdlib.h>
#include <string.h>

typedef struct resampler_context {
  AVCodecContext* audio_codec_context;
  frame_t* list;

  int samples_count;
} resampler_context_t;

AVFrame* allocate_audio_frame(enum AVSampleFormat sample_fmt, uint64_t channel_layout, int sample_rate,
			      int nb_samples) {
  AVFrame *frame = av_frame_alloc();
  int status = 0;
  
  if (!frame) {
    throw_error("Error allocating an audio frame", status);
  }
  
  frame->format = sample_fmt;
  frame->channel_layout = channel_layout;
  frame->sample_rate = sample_rate;
  frame->nb_samples = nb_samples;
  frame->pts = 0;
  
  if (nb_samples) {
    status = av_frame_get_buffer(frame, 0);
    if (status < 0) {
      throw_error("Error allocating an audio buffer", status);
    }
  }
  frame->nb_samples = 0;
  
  return frame;
}

void set_audio_timestamp(resampler_context_t* resampler_context, frame_t* frame) {
  struct frame_item* item = frame_get_item(frame);
  AVCodecContext* codec_context = resampler_context->audio_codec_context;
  AVFrame* avframe = (AVFrame*)item->buffer;

  resampler_context->samples_count += codec_context->frame_size;
  avframe->pts = av_rescale_q(resampler_context->samples_count,
			      (AVRational){ 1, codec_context->sample_rate }, codec_context->time_base);
}

void allocate_audio_frame_item(resampler_context_t* resampler_context) {
  AVCodecContext* codec_context = resampler_context->audio_codec_context;

  frame_t* resampled_frame = frame_last(resampler_context->list);
  frame_t* new_frame = frame_alloc(FRAME_AUDIO_TYPE);

  struct frame_item* item = frame_get_item(new_frame);
  item->stream_id = FRAME_AUDIO_TYPE;
  item->buffer = allocate_audio_frame(codec_context->sample_fmt, codec_context->channel_layout,
				      codec_context->sample_rate, codec_context->frame_size);

  frame_attach_to(resampled_frame, new_frame);
  set_audio_timestamp(resampler_context, new_frame);
}

void resample_audio_frame(resampler_context_t* resampler_context, frame_t* frame, int offset) {
  frame_t* resampled_frame = frame_last(resampler_context->list);

  struct frame_item* src_item = frame_get_item(frame);
  struct frame_item* dst_item = frame_get_item(resampled_frame);

  AVCodecContext* codec_context = resampler_context->audio_codec_context;
  AVFrame* src_avframe = (AVFrame*)src_item->buffer;
  AVFrame* dst_avframe = (AVFrame*)dst_item->buffer;
  
  int src_nb_samples = src_avframe->nb_samples - offset;
  int dst_nb_samples = codec_context->frame_size - dst_avframe->nb_samples;
  int min_nb_samples = fmin(src_nb_samples, dst_nb_samples);

  float** src_data = (float**)src_avframe->data;
  float** dst_data = (float**)dst_avframe->data;
  
  for (int i = 0; i < min_nb_samples; i++) {
    for (int j = 0; j < src_avframe->channels; j++) {
      dst_data[j][dst_avframe->nb_samples + i] = src_data[j][offset + i];
    }
  }
  dst_avframe->nb_samples += min_nb_samples;

  if ((src_nb_samples - min_nb_samples) > 0) {
    allocate_audio_frame_item(resampler_context);
    resample_audio_frame(resampler_context, frame, offset + min_nb_samples);
  }
}

void resampler_initialize(resampler_context_t** resampler_context, void* codec_context) {
  resampler_context_t* context = (resampler_context_t*)malloc(sizeof(resampler_context_t));
  AVCodecContext* codec_cxt = (AVCodecContext*)codec_context;
  
  context->list = frame_alloc(FRAME_AUDIO_TYPE);
  context->audio_codec_context = codec_cxt;
  context->samples_count = 0;
  
  struct frame_item* item = frame_get_item(context->list);
  item->stream_id = FRAME_AUDIO_TYPE;
  item->buffer = allocate_audio_frame(codec_cxt->sample_fmt, codec_cxt->channel_layout,
				      codec_cxt->sample_rate, codec_cxt->frame_size);
  
  *resampler_context = context;
}

void resampler_free(resampler_context_t** resampler_context) {
  resampler_context_t* context = *resampler_context;

  if (context->list) {
    frame_free(&context->list);
  }
  free(context);

  context = NULL;
}

void resampler_put_frame(resampler_context_t* resampler_context, frame_t* frame) { 
  resample_audio_frame(resampler_context, frame, 0);
}

frame_t* resampler_get_frame(resampler_context_t* resampler_context) {
  return resampler_context->list;
}
