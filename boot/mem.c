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

void init_memmap(struct MemoryMap *mem_map)
{
	unsigned long long status;
    mem_map->map_size = MEM_MAP_SIZE;
	status = ST->BootServices->GetMemoryMap(
		&mem_map->map_size, (struct EFI_MEMORY_DESCRIPTOR*)mem_map->buffer, &mem_map->map_key,
		&mem_map->descriptor_size, &mem_map->descriptor_version);
	assert(status, L"GetMemoryMap");
	mem_desc_num = mem_map->map_size / mem_map->descriptor_size;
}
