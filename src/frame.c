#include "frame.h"
#include "common/error.h"

#include <libavcodec/avcodec.h>
#include <stdlib.h>

typedef struct _frame {
  enum frame_type type;
  struct frame_item item;

  struct _frame* next;
  struct _frame* prev;
  struct _farme** last;
} frame_t;

frame_t* frame_alloc(enum frame_type type) {
  frame_t* frame = (frame_t*)malloc(sizeof(frame_t));
  frame->next = NULL;
  frame->prev = NULL;
  frame->last = NULL;
  frame->type = type;

  frame->item.buffer = av_frame_alloc();
  frame->item.stream_id = 0;

  if (!frame->item.buffer) {
    free(frame);
    return NULL;
  }
  
  return frame;
}

frame_t* frame_next(frame_t* frame) {
  if (!frame) {
    return NULL;
  }
  return frame->next;
}

frame_t* frame_last(frame_t* frame) {
  if (!frame->last) {
    return frame;
  }
  return *frame->last;
}

int frame_attach_to(frame_t* parent, frame_t* child) {
  if (parent->type != parent->type) {
    return -1;
  }

  if (parent->last == NULL) {
    parent->last = (frame_t**)malloc(sizeof(frame_t*));
    *parent->last = parent;
  }

  frame_t* last_frame = *parent->last;

  last_frame->next = child;
  child->prev = last_frame;
  
  child->last = last_frame->last;
  *child->last = child;
}

void frame_free(frame_t** frame) {
  if ((*frame) == NULL) {
    return;
  }
  frame_free(&((*frame)->next));

  if ((*frame)->prev == NULL) {
    if ((*frame)->next != NULL) {
      free((*frame)->last);
    }
  } else {
    (*frame)->prev->next = NULL;
  }

  if (*frame != NULL) {
    av_frame_free((AVFrame**)&((*frame)->item.buffer));
    free(*frame);
    frame = NULL;
  }
}

struct frame_item* frame_get_item(frame_t* frame) {
  return &frame->item;
}
