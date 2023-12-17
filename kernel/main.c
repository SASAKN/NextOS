#include "graphics.h"

//この関数がジャンプされてすぐに実行される
void kernel_main(struct fb_configuration fb_config) {
    //白を塗りつぶす
    unsigned char *fb = (unsigned char *)fb_config.base_addr;
    for (unsigned long long i = 0; i < fb_config.fb_size; ++i) {
        fb[i] = 255;
    }
    //処理が終わると
    while(1) __asm__ ("hlt");
}