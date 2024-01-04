#include "graphics.h"

//この関数がジャンプされてすぐに実行される
void kernel_main(struct *fb_config) {
    while(1) __asm__ ("hlt");
};

