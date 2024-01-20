#include <neos/types.h>
#include "bp.h"


void kernel_main(const fb_config *fb_con) {
    for (uint64_t i = 0; i < fb_con->fb_size; i++) {
        fb_con->base[i] = i % 256;
    }
    while(1) __asm__ ("hlt");
}

