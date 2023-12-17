#include "graphics.h"

//この関数がジャンプされてすぐに実行される



void kernel_main(unsigned char *fb, unsigned long long fb_size) {
    //白を塗りつぶす
    for (unsigned long long i = 0; i < fb_size; ++i) {
        fb[i] = 255;
    }
    //処理が終わると
    while(1) __asm__ ("hlt");
}