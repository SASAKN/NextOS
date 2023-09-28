/* Neos Boot Memory Manager v.0.1 */

#include "include/types.h"
#include "include/status.h"
#include "include/config.h"
#include "include/efi.h"
#include "include/elf.h"
#include "include/proto.h"
#include "include/graphics.h"
#include "include/mem.h"

/* NEOSのブート中のメモリー管理 */
EFI_STATUS GetMemoryMap(struct MemoryMap *mem_map) {
    if (mem_map->buffer == NULL) {
        return EFI_BUFFER_TOO_SMALL;
    };
    /* もしエラーを返さないなら */
    init_memorymap();
};

void init_memorymap(void)
