#include <neos/types.h>
#include "include/bp.h"
#include "include/graphics.h"

void kernel_main(const fb_config *fb_con) {
    while(1) __asm__ ("hlt");
}

