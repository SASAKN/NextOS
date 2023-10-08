/* Neos Boot Memory Manager v.0.1 */

#include "include/types.h"
#include "include/status.h"
#include "include/config.h"
#include "include/efi.h"
#include "include/elf.h"
#include "include/proto.h"
#include "include/graphics.h"
#include "include/mem.h"


unsigned char mem_desc[MEM_MAP_SIZE];
unsigned long long mem_desc_num;
unsigned long long mem_desc_unit_size;
unsigned long long map_key;

void dump_memmap(void)
{
	struct EFI_MEMORY_DESCRIPTOR *p =
		(struct EFI_MEMORY_DESCRIPTOR *)mem_desc;
	unsigned int i;

	for (i = 0; i < mem_desc_num; i++) {
		puth((unsigned long long)p, 16);
		putc(L' ');
		puth(p->Type, 2);
		putc(L' ');
		puth(p->PhysicalStart, 16);
		putc(L' ');
		puth(p->VirtualStart, 16);
		putc(L' ');
		puth(p->NumberOfPages, 16);
		putc(L' ');
		puth(p->Attribute, 16);
		puts(L"\r\n");

		p = (struct EFI_MEMORY_DESCRIPTOR *)(
			(unsigned char *)p + mem_desc_unit_size);
	}
}

void init_memmap(void)
{
	unsigned long long status;
	unsigned long long mmap_size = MEM_DESC_SIZE;
	unsigned int desc_ver;

	status = ST->BootServices->GetMemoryMap(
		&mmap_size, (struct EFI_MEMORY_DESCRIPTOR *)mem_desc, &map_key,
		&mem_desc_unit_size, &desc_ver);
	assert(status, L"GetMemoryMap");
	mem_desc_num = mmap_size / mem_desc_unit_size;
}