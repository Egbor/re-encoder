#ifndef _RESAMPLER_H_
#define _RESAMPLER_H_

#include "frame.h"

typedef struct resampler_context resampler_context_t;

extern void resampler_initialize(resampler_context_t** resampler_context, void* codec_context);
extern void resampler_free(resampler_context_t** resampler_context);

extern void resampler_put_frame(resampler_context_t* resampler_context, frame_t* frame);
extern frame_t* resampler_get_frame(resampler_context_t* resampler_context);

#endif
