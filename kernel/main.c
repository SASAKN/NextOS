#include "graphics.h"

//この関数がジャンプされてすぐに実行される
void kernel_main(void) {
    //CPU Halt
    while(1) __asm__ ("hlt");
}