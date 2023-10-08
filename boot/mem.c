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

/* メモリマップの種類 */
UINT16 *get_memtype_name(EFI_MEMORY_TYPE type)
{
	switch (type)
	{
	case EfiReservedMemoryType:
		return L"EfiReservedMemoryType";
	case EfiLoaderCode:
		return L"EfiLoaderCode";
	case EfiLoaderData:
		return L"EfiLoaderData";
	case EfiBootServicesCode:
		return L"EfiBootServicesCode";
	case EfiBootServicesData:
		return L"EfiBootServicesData";
	case EfiRuntimeServicesCode:
		return L"EfiRuntimeServicesCode";
	case EfiRuntimeServicesData:
		return L"EfiRuntimeServicesData";
	case EfiConventionalMemory:
		return L"EfiConventionalMemory";
	case EfiUnusableMemory:
		return L"EfiUnusableMemory";
	case EfiACPIReclaimMemory:
		return L"EfiACPIReclaimMemory";
	case EfiACPIMemoryNVS:
		return L"EfiACPIMemoryNVS";
	case EfiMemoryMappedIO:
		return L"EfiMemoryMappedIO";
	case EfiMemoryMappedIOPortSpace:
		return L"EfiMemoryMappedIOPortSpace";
	case EfiPalCode:
		return L"EfiPalCode";
	case EfiPersistentMemory:
		return L"EfiPersistentMemory";
	case EfiMaxMemoryType:
		return L"EfiMaxMemoryType";
	default:
		return L"InvalidMemoryType";
	}
}

void print_memmap(void)
{
	struct EFI_MEMORY_DESCRIPTOR *p =
		(struct EFI_MEMORY_DESCRIPTOR *)mem_desc;
	unsigned int i;
	UINT16 *header = L"Index, Type, Type(name), PhysicalStart, NumberOfPages, Attribute\n";
	puts(header);
	puts(L"\r\n");
	for (i = 0; i < mem_desc_num; i++)
	{
		PrintHex((unsigned long long)p, 16);
		putc(L' ');
		PrintHex(p->Type, 2);
		putc(L' ');
		puts(get_memtype_name(p->Type));
		putc(L' ');
		PrintHex(p->PhysicalStart, 16);
		putc(L' ');
		PrintHex(p->VirtualStart, 16);
		putc(L' ');
		PrintHex(p->NumberOfPages, 16);
		putc(L' ');
		PrintHex(p->Attribute, 16);
		puts(L"\r\n");

		p = (struct EFI_MEMORY_DESCRIPTOR *)((unsigned char *)p + mem_desc_unit_size);
	}
}

EFI_STATUS init_memmap(struct MemoryMap* map)
{
	if (map->buffer == NULL) {
		return EFI_BUFFER_TOO_SMALL;
	}

  map->map_size = map->buffer_size;
  return gBS->GetMemoryMap(
      &map->map_size,
      (EFI_MEMORY_DESCRIPTOR*)map->buffer,
      &map->map_key,
      &map->descriptor_size,
      &map->descriptor_version);
};

EFI_STATUS save_memmap(struct MemoryMap *map, EFI_FILE_PROTOCOL *file) {
	CHAR8 buf[256];
	UINTN length;

	CHAR8* header = "Index, Type, Type(name), PhysicalStart, NumberOfPages, Attribute\n";
	length = strlen(header);
	file->Write(file, &length, header);

}