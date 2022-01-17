#ifndef _DECODER_H_
#define _DECODER_H_

#include "frame.h"

#include <stddef.h>

typedef struct _decoder_context decoder_context_t;

extern void decoder_open(decoder_context_t** decoder_context, const char* filename, float start_ts,
			 float end_ts);
extern void decoder_close(decoder_context_t** decoder_context);

extern frame_t* decoder_next_frame(decoder_context_t* decoder_context);

#endif
