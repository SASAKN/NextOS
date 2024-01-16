#include "graphics.h"
#include "bp.h"

//この関数がジャンプされてすぐに実行される
void kernel_main() {
    while(1) __asm__ ("hlt");
};

