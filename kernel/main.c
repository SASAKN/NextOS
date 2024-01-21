#include <neos/types.h>
#include "include/graphics.h"
#include "include/proto.h"

void kernel_main(const fb_config *fb_con) {
    fb bg;
    bg.r = 66;
    bg.g = 135;
    bg.b = 245;
    for (uint32_t x = 0; x < fb_con->hr; ++x) {
        for (uint32_t y = 0; y < fb_con->vr; ++y) {
            write_pixel(fb_con, x, y, &bg);
        }
    }
    while(TRUE) __asm__ ("hlt");
}

