/* Neos Boot Memory Manager v.0.1 */

#include "include/types.h"
#include "include/status.h"
#include "include/config.h"
#include "include/efi.h"
#include "include/elf.h"
#include "include/proto.h"
#include "include/graphics.h"
#include "include/mem.h"

/* メモリーマップを表示 */
void print_memmap(struct MemoryMap *mem_map) {
    EFI_MEMORY_DESCRIPTOR *p = (EFI_MEMORY_DESCRIPTOR *)mem_map->buffer;
    UINT32 i;

    for (i = 0; i < mem_map->map_size; i++) {
		PrintHex((UINT64)p, 16);
		putc(L' ');
		PrintHex(p->Type, 2);
		putc(L' ');
		PrintHex(p->PhysicalStart, 16);
		putc(L' ');
		PrintHex(p->VirtualStart, 16);
		putc(L' ');
		PrintHex(p->NumberOfPages, 16);
		putc(L' ');
		PrintHex(p->Attribute, 16);
		puts(L"\r\n");

		p = (EFI_MEMORY_DESCRIPTOR *)(
			(UINT8 *)p + mem_map->descriptor_size);
	}
}

/* メモリーマップの初期化 */
void init_memmap(struct MemoryMap *mem_map)
{
	unsigned long long status;
    mem_map->map_size = MEM_MAP_SIZE;
	status = ST->BootServices->GetMemoryMap(
		&mem_map->map_size, (struct EFI_MEMORY_DESCRIPTOR*)mem_map->buffer, &mem_map->map_key,
		&mem_map->descriptor_size, &mem_map->descriptor_version);
	assert(status, L"GetMemoryMap");
	mem_map->map_size = mem_map->map_size / mem_map->descriptor_size;
}
