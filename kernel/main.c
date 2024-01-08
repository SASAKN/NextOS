#include "graphics.h"

//この関数がジャンプされてすぐに実行される
void kernel_main(void) {
    (struct)
    while(1) __asm__ ("hlt");
};

