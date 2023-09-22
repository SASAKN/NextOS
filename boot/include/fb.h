#ifndef _FB_H
#define _FB_H

struct frame_buffer {
    unsigned long long base;
    unsigned long long size;
    unsigned int hr;
    unsigned int vr;
};

extern struct frame_buffer frame_buffer;

/* Prototype */
void init_frame_buffer(void);

#endif