#ifndef _RESCALER_H_
#define _RESCALER_H_

#include "frame.h"

typedef struct rescaler_context rescaler_context_t;

extern void rescaler_initialize(rescaler_context_t** rescaler_context, void* codec_context);
extern void rescaler_free(rescaler_context_t** rescaler_context);

extern void rescaler_put_frame(rescaler_context_t* rescaler_context, frame_t* frame);
extern frame_t* rescaler_get_frame(rescaler_context_t* rescaler_context);

#endif
