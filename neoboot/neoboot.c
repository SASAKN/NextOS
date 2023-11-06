#include "uefi/uefi.h"

int main( int argc, char **argv ) {
    printf("Hello World!\n");
    printf("Boot Success ! (hlt)\n");
    /* hltないと処理が進んでしまう */
    while (1) __asm__ ("hlt");
    return EFI_SUCCESS;
}