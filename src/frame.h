#ifndef _FRAME_H_
#define _FRAME_H_

typedef struct _frame frame_t;

enum frame_type { FRAME_VIDEO_TYPE, FRAME_AUDIO_TYPE };

struct frame_item {
  void* buffer;
  int stream_id;
};

extern frame_t* frame_alloc(enum frame_type type);
extern frame_t* frame_next(frame_t* frame);
extern frame_t* frame_last(frame_t* frame);

extern int frame_attach_to(frame_t* parent, frame_t* child);
extern void frame_free(frame_t** frame);

struct frame_item* frame_get_item(frame_t* frame);

#endif
