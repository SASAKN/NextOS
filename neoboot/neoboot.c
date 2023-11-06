#include "uefi/uefi.h"

int main( int argc, char **argv ) {
    printf("Hello World!\n");
    __asm__ volatile("hlt");
}