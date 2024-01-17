#include "graphics.h"
#include "bp.h"

//この関数がジャンプされてすぐに実行される
void kernel_main(struct _boot_param bp) {
    //白く塗りつぶしてみるか
    unsigned char *fb = (unsigned char *)bp.fb_setting.base_addr;
    for( unsigned long long i = 0; i < bp.fb_setting.fb_size; i++ ) {
        fb[i] = 255;
    }

    //とりあえず、Printせずにできるもので
    __asm__ volatile ("movl %0 %%rdi;"
                      : "r"(bp.fb_setting.base_addr));
    __asm__ volatile ("movl %0 %%rsi;"
                      : "r"(bp.fb_setting.fb_size));
    __asm__ volatile ("movl %0 %%rdx;"
                      : "r"(bp.fb_setting.pixels_per_scan_line));
    while(1) __asm__ volatile ("hlt");
};

