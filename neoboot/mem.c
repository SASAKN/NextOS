#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"
#include "include/macros.h"
#include "include/status.h"

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
};

void print_memmap(struct MemoryMap *map)
{
	EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
	UINT32 i;
	UINT16 *header = L"Index, Buffer, Type, Type(name),PhysicalStart, VirtualStart, NumberOfPages, Attribute\n";
	custom_printf("[ INFO ] MemoryMap\n");
	puts(header);
	putc(L' ');
	for (i = 0; i < map->memmap_desc_entry; i++)
	{
		PrintHex((unsigned long long)i, 2);
		putc(L' ');
		PrintHex((unsigned long long)desc, 16);
		putc(L' ');
		PrintHex(desc->Type, 2);
		putc(L' ');
		puts(get_memtype_name(desc->Type));
		putc(L' ');
		PrintHex(desc->PhysicalStart, 16);
		putc(L' ');
		PrintHex(desc->VirtualStart, 16);
		putc(L' ');
		PrintHex(desc->NumberOfPages, 16);
		putc(L' ');
		PrintHex(desc->Attribute, 16);
		puts(L"\r\n");
		desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)desc + map->descriptor_size);
	};
};