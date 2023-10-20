/* Neos Boot Memory Manager v.0.1 */

#include "include/types.h"
#include "include/status.h"
#include "include/config.h"
#include "include/efi.h"
#include "include/elf.h"
#include "include/proto.h"
#include "include/graphics.h"
#include "include/mem.h"

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
	char buffer[2000];
	UINT16 *header = L"Index, Buffer, Type, Type(name),PhysicalStart, VirtualStart, NumberOfPages, Attribute\n";
	puts(header);
	putc(L' ');
	for (i = 0; i < map->memmap_desc_entry; i++)
	{
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
		text_gen(buffer, sizeof(buffer), "%u : %x, %02lx, %-ls, %016lx, %016lx, %016lx, %016lx \n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->Attribute);
		custom_printf("%s\n", buffer);
		desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)desc + map->descriptor_size);
	};
};

EFI_STATUS init_memmap(struct MemoryMap *map)
{
	unsigned long long status;
	status = ST->BootServices->GetMemoryMap(
		&map->map_size, (struct EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key,
		&map->descriptor_size, &map->descriptor_version);
	assert(status, L"GetMemoryMap");
	map->memmap_desc_entry = map->map_size / map->descriptor_size;
	return status;
};



void save_memmap(struct MemoryMap *map, EFI_FILE_PROTOCOL *file) {
	EFI_STATUS status;
	UINT64 size;
	char buffer[2000];
	char tmp[100];
	EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
	UINT32 i;
	/* ヘッダーの書き込み */
	char *header = "Index, Buffer, Type, Type(name),PhysicalStart, VirtualStart, NumberOfPages, Attribute\n";
	size = strlen(header);
	text_gen(tmp, sizeof(tmp), "%u", size);
	custom_printf("[Size] %s", tmp);
	file->Write(file, &size, header);
	for (i = 0; i < map->memmap_desc_entry; i++)
	{
		text_gen(buffer, sizeof(buffer), "%u : %x, %-ls, %x, %x, %x", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->Attribute);
		custom_printf("%s", buffer);
		size = strlen(buffer);
		file->Write(file, &size, buffer);
		desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)desc + map->descriptor_size);
	};
};