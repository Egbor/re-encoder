#include "rescaler.h"
#include "common/error.h"

#include <libavutil/imgutils.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>

#include <stdlib.h>

#define DEFAULT_WIDTH 720
#define DEFAULT_HEIGHT 400
#define DEFAULT_FORMAT AV_PIX_FMT_YUV420P

typedef struct rescaler_context {
  AVCodecContext* video_codec_context;
  struct SwsContext* sws_context;
  
  frame_t* list;
} rescaler_context_t;

AVFrame* allocate_video_frame(enum AVPixelFormat pix_fmt, int width, int height, int pts, int dts) {
  AVFrame* frame = av_frame_alloc();
  int status = 0;

  if (!frame) {
    throw_error("Error allocating an audio frame", status);
  }

  frame->format = pix_fmt;
  frame->width = width;
  frame->height = height;
  frame->pts = pts;
  frame->pkt_dts = dts;

  if ((frame->width > 0) && (frame->height > 0)) {
    status = av_frame_get_buffer(frame, 0);
    if (status < 0) {
      throw_error("Error allocating a video buffer", status);
    }
  }

  return frame;
}

struct SwsContext* allocate_video_scaler(AVCodecContext* codec_context) {
  int src_width = DEFAULT_WIDTH;
  int src_height = DEFAULT_HEIGHT;
  int src_format = DEFAULT_FORMAT;

  int dst_width = codec_context->width;
  int dst_height = codec_context->height;
  int dst_format = codec_context->pix_fmt;

  return sws_getContext(src_width, src_height, src_format,
			dst_width, dst_height, dst_format,
			SWS_BILINEAR, NULL, NULL, NULL);
}

void scale_video_frame(rescaler_context_t* rescaler_context, frame_t* src_frame, frame_t* dst_frame) {
  struct frame_item* src_item = frame_get_item(src_frame);
  struct frame_item* dst_item = frame_get_item(dst_frame);

  AVCodecContext* codec_context = rescaler_context->video_codec_context;
  AVFrame* src_avframe = (AVFrame*)src_item->buffer;
  AVFrame* dst_avframe = allocate_video_frame(codec_context->pix_fmt,
					      codec_context->width, codec_context->height,
					      src_avframe->pts, src_avframe->pkt_dts);

  if (src_avframe->pts != AV_NOPTS_VALUE) {
    dst_avframe->pts = av_rescale_q(src_avframe->pts, (AVRational){1, 1000},
				    codec_context->time_base);
  }
  if (src_avframe->pkt_dts != AV_NOPTS_VALUE) {
    dst_avframe->pkt_dts = av_rescale_q(src_avframe->pkt_dts, (AVRational){1, 1000},
					codec_context->time_base);
  }

  sws_scale(rescaler_context->sws_context, (const uint8_t* const*)src_avframe->data,
	    src_avframe->linesize, 0, src_avframe->height, dst_avframe->data, dst_avframe->linesize);
  
  dst_item->stream_id = src_item->stream_id;
  dst_item->buffer = dst_avframe;
}

void put_video_frame(rescaler_context_t* rescaler_context, frame_t* frame) {
  if (!rescaler_context->list) {
    rescaler_context->list = frame; 
  } else {
    frame_t* last_frame = frame_last(rescaler_context->list);
    frame_attach_to(last_frame, frame);
  }
}

void rescaler_initialize(rescaler_context_t** rescaler_context, void* codec_context) {
  rescaler_context_t* context = (rescaler_context_t*)malloc(sizeof(rescaler_context_t));
  
  context->list = NULL;
  context->video_codec_context = (AVCodecContext*)codec_context;
  context->sws_context = allocate_video_scaler(codec_context);

  *rescaler_context = context;
}

void rescaler_free(rescaler_context_t** rescaler_context) {
  rescaler_context_t* context = *rescaler_context;

  if (!context->list) {
    frame_free(&context->list);
  }
  sws_freeContext(context->sws_context);
  free(context);

  context = NULL;
}

void rescaler_put_frame(rescaler_context_t* rescaler_context, frame_t* frame) {
  frame_t* new_frame = frame_alloc(FRAME_VIDEO_TYPE);

  scale_video_frame(rescaler_context, frame, new_frame);
  put_video_frame(rescaler_context, new_frame);
}

frame_t* rescaler_get_frame(rescaler_context_t* rescaler_context) {
  return rescaler_context->list;
}
