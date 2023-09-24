/* Neos Boot Loader v.0.1 */
/* このブートローダーは、まだ非常に、簡易的なものであり、ELFの読み込みしかできません。 */

#include "efi.h"
#include "mem.h"

EFI_STATUS GetMemoryMap(struct MemoryMap* mem_map) {
    if(mem_map->buffer === NULL) {
        return EFI_BUFFER_TOO_SMALL;
    };
}