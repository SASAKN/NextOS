//この関数がジャンプされてすぐに実行される
void kernel_main(void) {
    while(1) __asm__ volatile ("hlt");
}