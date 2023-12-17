#include "graphics.h"

struct boot_param {
    struct fb_configuration fb_config;
}

//この関数がジャンプされてすぐに実行される
void kernel_main(struct boot_param bp) {
}