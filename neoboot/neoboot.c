#include "efilib/inc/efi.h"
#include "efilib/inc/efilib.h"
#include "include/elf.h"
#include "include/memmap.h"
#include "include/param.h"

#define MAX(a, b) (a < b ? b : a)
#define MIN(a, b) (a < b ? a : b)

void print_efi_configuration_table(void)
{
    uint64_t i;
    Print(L"\n[ INFO ] EfiConfigurationTable\n");
    for (i = 0; i < ST->NumberOfTableEntries; i++)
    {
        Print(L"%02d : %016x : %08x, %04x, %04x\n", i, (unsigned long long)&ST->ConfigurationTable[i], ST->ConfigurationTable[i].VendorGuid.Data1, ST->ConfigurationTable[i].VendorGuid.Data2, ST->ConfigurationTable[i].VendorGuid.Data3);
        unsigned char j;
        for (j = 0; j < 8; j++)
        {
            Print(L"%02x", ST->ConfigurationTable[i].VendorGuid.Data4[j]);
        }
        Print(L"%016x\n", (unsigned long long)ST->ConfigurationTable[i].VendorTable);
    }
    Print(L"\n");
    PrintOK();
    Print(L"VendorTable\n");
};

CHAR16 *get_memtype_name(EFI_MEMORY_TYPE type)
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

void PrintOK() {
    ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
    Print(L"[ OK ]");
    ST->ConOut->SetAttribute(ST->ConOut, EFI_WHITE);
}

void PrintError() {
    ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
    Print(L"[ Error ]");
    ST->ConOut->SetAttribute(ST->ConOut, EFI_WHITE);
}

void PrintWarn() {
    ST->ConOut->SetAttribute(ST->ConOut, EFI_YELLOW);
    Print(L"[ Warn ]");
    ST->ConOut->SetAttribute(ST->ConOut, EFI_WHITE);
}

void PrintGoodBye() {
    ST->ConOut->SetAttribute(ST->ConOut, EFI_BLUE);
    Print(L"[ GoodBye ]");
    ST->ConOut->SetAttribute(ST->ConOut, EFI_WHITE);
}

//EDK2から移植
UINTN EFIAPI AsciiSPrint( OUT CHAR8 *StartOfBuffer,IN  UINTN BufferSize,IN CONST CHAR8  *FormatString, ...){
  va_list  Marker;
  UINTN    size;
  va_start (Marker, FormatString);
  size = AsciiVSPrint(StartOfBuffer, BufferSize, FormatString, Marker);
  va_end (Marker);
  return size;
}

UINTN EFIAPI AsciiStrLen ( IN CONST CHAR8 *String )
{
  UINTN  Length;
  ASSERT (String != NULL);
  while (String[Length] != '\0') {
    Length++;
  }
  return Length;
}

//@End EDK2から移植

EFI_STATUS print_memmap(struct MemoryMap *map) {
    EFI_STATUS status;
    Print(L"\n[ INFO ] MemoryMap\n");
    CHAR16 *header = L"Index, Buffer, Type, Type(name),PhysicalStart, VirtualStart, NumberOfPages, Size,  Attribute";
    Print(L"%s\n", header);
    uint32_t i;
    EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
    for (i = 0; i < map->memmap_desc_entry; i++) {
        Print(L"%02d, %016x, %02x, %s, %016x, %016x, %016x, %d, %016x",  i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        desc = (efi_memory_descriptor_t *)((uint8_t *)desc + map->descriptor_size);
    }
    Print(L"\n");
    PrintOK();
    Print(L"Print Memory Map\n");
    return EFI_SUCCESS;
}

EFI_STATUS save_memmap(struct MemoryMap *map, EFI_FILE_PROTOCOL *file) {
    CHAR8 buf[300];
    UINTN size;
    CHAR8 *header = "Index, Buffer, Type, Type(name),PhysicalStart, VirtualStart, NumberOfPages, Size,  Attribute";
    size = AsciiStrLen(header);
    uefi_call_wrapper(file->Write, 3, file, &size, header);
    EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
    for (uint32_t i = 0; i < map->memmap_desc_entry; i++){
        size = AsciiSPrint(buf, sizeof(buf), "%02d, %016x, %02x, %s, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        uefi_call_wrapper(file->Write, 3, file, &size, buf);
        desc = (EFI_MEMORY_DESCRIPTOR *)((uint8_t *)desc + map->descriptor_size);
    }
    PrintOK();
    Print(L"Save Memory Map\n");
    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    uefi_call_wrapper(ST->BootServices->SetWatchdogTimer, 4, 0, 0, 0, NULL);
    //Welcome
    PrintOK();
    Print(L"Welcome to NeoBoot v.0.1");
    //Get MemoryMap
    struct MemoryMap map;
    EFI_MEMORY_DESCRIPTOR *efi_map = LibMemoryMap(map.memmap_desc_entry, map.map_key, map.descriptor_size, map.descriptor_version);
    map.memmap_desc_entry = map.map_size / map.descriptor_size;
    ASSERT(map != NULL);
    PrintOK();
    Print(L"Get Memory Map");
    // Print MemoryMap
    print_memmap(&map);
    // Save Memory Map
    // GoodBye
    PrintGoodBye();
    Print(L"BootLoader");
}