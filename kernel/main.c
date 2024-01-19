#include "graphics.h"
#include "bp.h"

//この関数がジャンプされてすぐに実行される
void kernel_main(const struct _boot_param bp) {
    
    while(1) __asm__ volatile ("hlt");
};

