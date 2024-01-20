#include "../../include/proto.h"

void halt(void) {
    __asm__ volatile ("hlt");
}