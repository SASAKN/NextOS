#include <neos/types.h>



void kernel_main(void) {
    char a = 'a';
    arch_serial_write(a);
    while(1) __asm__ ("hlt");
}

