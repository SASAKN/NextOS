#ifndef _FB_H
#define _FB_H

#include "types.h" /* Must be First. */

/* FrameBuffer */
struct frame_buffer {
    unsigned long long base;
    unsigned long long size;
    unsigned int hr;
    unsigned int vr;
};

/* RECT */
struct RECT {
    UINT32 x, y;
    UINT32 w, h;
};

/* Prototype */
void init_frame_buffer(void);

/* Extern */
extern struct frame_buffer frame_buffer;

#endif