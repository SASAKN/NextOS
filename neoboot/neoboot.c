#include "uefi/uefi.h"
#include "include/mem.h"

int main( int argc, char **argv ) {
    printf("Hello World!\n");
    printf("Boot Success ! (hlt)\n");
    // Get Memory Map
    char_t map_buf[]
    struct MemoryMap map;
    map.map_size = 0;
    map.map_key = 0;
    map
    BS->GetMemoryMap()
    // hltがないと処理が進んでしまう
    while (1) __asm__ ("hlt");
    return EFI_SUCCESS;
}