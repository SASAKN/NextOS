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
    Print(L"[ OK ]");
    ST->ConOut->SetAttribute(ST->ConOut, EFI_WHITE);
}

EFI_STATUS EFIAPI main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    SIMPLE_TEXT_OUTPUT_PROTOCOL *conout = ST->ConOut;
    ST->BootServices->SetWatchdogTimer(0,0,0,NULL);
    //Welcome
    PrintOK();
    Print(L"Welcome to NeoBoot v.0.1");
    //Get MemoryMap
    struct MemoryMap map;
    EFI_MEMORY_DESCRIPTOR *efi_map = LibMemoryMap(map.memmap_desc_entry, map.map_key, map.descriptor_size, map.descriptor_version);
    ASSERT(map != NULL);
    PrintOK();
    Print(L"Get Memory Map");
    // Print MemoryMap

    // GoodBye
    PrintGoodBye();
    Print(L"BootLoader");
}