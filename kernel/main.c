#include <neos/types.h>
#include "bp.h"


void kernel_main(const struct _boot_param *bp) {
    
    while(1) __asm__ ("hlt");
}

