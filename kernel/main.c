#include <neos/types.h>
#include "include/graphics.h"
#include "include/proto.h"

void kernel_main(const fb_config *fb_con) {
    // BackGroundを作成
    fb bg; //青色
    bg.r = 66;
    bg.g = 135;
    bg.b = 245;

    for (uint32_t x = 0; x < fb_con->hr; ++x) {
        for (uint32_t y = 0; y < fb_con->vr; ++y) {
            write_pixel(fb_con, x, y, &bg);
        }
    }

    //テキスト表示
    fb text_color;
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
    int i = 0;
    for (char c = '!'; c <= '~'; ++c, ++i) {
        write_ascii(fb_con, 8 * i, 50, c, &text_color);
    }
    
    while(TRUE) __asm__ ("hlt");
}

