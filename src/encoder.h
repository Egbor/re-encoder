#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "frame.h"

typedef struct _encoder_context encoder_context_t;

extern void encoder_open(encoder_context_t** encoder_context, const char* filename);
extern void encoder_close(encoder_context_t** encoder_context);

extern void encoder_next_frame(encoder_context_t* encoder_context, frame_t* frame);
extern void encoder_set_frames(encoder_context_t* encoder_context, frame_t* video_frame,
			       frame_t* audio_frame);
extern void* encoder_get_codec_context(encoder_context_t* encoder_context, int media_type);

#endif
