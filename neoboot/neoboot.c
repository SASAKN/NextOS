#include "efilib/inc/efi.h"
#include "efilib/inc/efilib.h"
#include "include/elf.h"
#include "include/memmap.h"
#include "include/param.h"

#define MAX(a, b) (a < b ? b : a)
#define MIN(a, b) (a < b ? a : b)

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
    // Save MemoryMap
    
    // GoodBye
    PrintGoodBye();
    Print(L"BootLoader");
}