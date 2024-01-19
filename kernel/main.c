#include <neos/types.h>


void kernel_main(const struct _boot_param *bp) {
    for (unsigned long long i = 0; i < bp->fb_setting.fb_size; i++) {
        bp->fb_setting.base[i] =  i % 255;
    }
    while(1) __asm__ ("hlt");
}

