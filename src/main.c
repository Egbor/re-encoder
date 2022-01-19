#include "common/basename.h"
#include "common/error.h"

#include <libavformat/avformat.h>
#include <stdlib.h>

#include "decoder.h"
#include "encoder.h"
#include "rescaler.h"
#include "resampler.h"

int main(int argc, char* argv[]) {
  set_basename(argv[0]);

  if (argc < 5) {
    throw_error("Not enought arguments.", -1);
  }
  
  frame_t* frame = NULL;
  decoder_context_t* decoder_context = NULL;
  encoder_context_t* encoder_context = NULL;

  rescaler_context_t* rescaler_context = NULL;
  resampler_context_t* resampler_context = NULL;

  float start_timestamp = (float)strtol(argv[2], NULL, 10);
  float end_timestamp = (float)strtol(argv[3], NULL, 10);
  
  av_register_all();
  
  decoder_open(&decoder_context, argv[1], start_timestamp, end_timestamp);
  encoder_open(&encoder_context, argv[4]);

  void* video_codec_context = encoder_get_codec_context(encoder_context, FRAME_VIDEO_TYPE);
  void* audio_codec_context = encoder_get_codec_context(encoder_context, FRAME_AUDIO_TYPE);

  rescaler_initialize(&rescaler_context, video_codec_context);
  resampler_initialize(&resampler_context, audio_codec_context);

  while ((frame = decoder_next_frame(decoder_context)) != NULL) {
    struct frame_item* item = frame_get_item(frame);
    if (item->stream_id == FRAME_VIDEO_TYPE) {
      rescaler_put_frame(rescaler_context, frame);
    } else if (item->stream_id == FRAME_AUDIO_TYPE) {
      resampler_put_frame(resampler_context, frame);
    }
    frame_free(&frame);
  }

  frame_t* video_frame = rescaler_get_frame(rescaler_context);
  frame_t* audio_frame = resampler_get_frame(resampler_context);
  
  encoder_set_frames(encoder_context, video_frame, audio_frame);

  encoder_close(&encoder_context);
  decoder_close(&decoder_context);
  rescaler_free(&rescaler_context);
  resampler_free(&resampler_context);
  
  return 0;
}
