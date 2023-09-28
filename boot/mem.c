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
EFI_STATUS GetMemoryMap(struct MemoryMap *mem_map)
{
    if (mem_map->buffer == NULL)
    {
        return EFI_BUFFER_TOO_SMALL;
    };
    map->map_size = map->buffer_size;
    return BS->GetMemoryMap(&map->map_size, (EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key, &map->descriptor_size, &map->descriptor_version);
};
