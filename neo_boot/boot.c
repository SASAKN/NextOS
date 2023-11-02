#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"
#include "include/macros.h"

EFI_GUID gEfiFileInfoGuid = {0x9576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

EFI_STATUS GetMemoryMap(struct MemoryMap *map)
{
    if (map->buffer == NULL)
    {
        return EFI_BUFFER_TOO_SMALL;
    }

    map->map_size = map->buffer_size;
    return ST->BootServices->GetMemoryMap(
        &map->map_size,
        (EFI_MEMORY_DESCRIPTOR *)map->buffer,
        &map->map_key,
        &map->descriptor_size,
        &map->descriptor_version);
}

const CHAR16 *GetMemoryTypeUnicode(EFI_MEMORY_TYPE type)
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

EFI_STATUS SaveMemoryMap(struct MemoryMap *map, EFI_FILE_PROTOCOL *file)
{
    CHAR8 buf[256];
    UINTN len;

    CHAR8 *header =
        "Index, Type, Type(name), PhysicalStart, NumberOfPages, Attribute\n";
    len = strlen(header);
    file->Write(file, &len, header);

    custom_printf("map->buffer = %x, map->map_size = %x\n", map->buffer, map->map_size);

    EFI_PHYSICAL_ADDRESS iter;
    int i;
    for (iter = (EFI_PHYSICAL_ADDRESS)map->buffer, i = 0;
         iter < (EFI_PHYSICAL_ADDRESS)map->buffer + map->map_size;
         iter += map->descriptor_size, i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)iter;
        // len = AsciiSPrint(
        //     buf, sizeof(buf),
        //     "%u, %x, %-ls, %08lx, %lx, %lx\n",
        //     i, desc->Type, GetMemoryTypeUnicode(desc->Type),
        //     desc->PhysicalStart, desc->NumberOfPages,
        //     desc->Attribute & 0xffffflu);
        text_gen(buf, sizeof(buf), "%u, %x, %-ls, %x, %x, %x\n", i, desc->Type, GetMemoryTypeUnicode(desc->Type), desc->PhysicalStart, desc->NumberOfPages, desc->Attribute & 0xffffflu);
        len = strlen(buf);
        file->Write(file, &len, buf);
    }

    return EFI_SUCCESS;
}

EFI_STATUS OpenRootDir(EFI_HANDLE image_handle, EFI_FILE_PROTOCOL **root)
{
    EFI_LOADED_IMAGE_PROTOCOL *loaded_image;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs;

    ST->BootServices->OpenProtocol(
        image_handle,
        &lip_guid,
        (VOID **)&loaded_image,
        image_handle,
        NULL,
        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);

    ST->BootServices->OpenProtocol(
        loaded_image->DeviceHandle,
        &fi_guid,
        (VOID **)&fs,
        image_handle,
        NULL,
        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);

    fs->OpenVolume(fs, root);

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI EfiMain(
    EFI_HANDLE image_handle,
    EFI_SYSTEM_TABLE *system_table)
{
    efi_init(system_table);
    custom_printf("Hello, Mikan World!\n");

    CHAR8 memmap_buf[2000];
    struct MemoryMap memmap;
    memmap.buffer = memmap_buf;
    memmap.buffer_size = 2000;
    init_memmap(&memmap);

    EFI_FILE_PROTOCOL *root_dir;
    OpenRootDir(image_handle, &root_dir);

    EFI_FILE_PROTOCOL *memmap_file;
    root_dir->Open(
        root_dir, &memmap_file, L"\\memmap",
        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);

    SaveMemoryMap(&memmap, memmap_file);
    memmap_file->Close(memmap_file);

    // #@@range_begin(read_kernel)
    EFI_FILE_PROTOCOL *kernel_file;
    root_dir->Open(
        root_dir, &kernel_file, L"\\kernel.elf",
        EFI_FILE_MODE_READ, 0);

    UINTN file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12;
    UINT8 file_info_buffer[file_info_size];
    kernel_file->GetInfo(
        kernel_file, &gEfiFileInfoGuid,
        file_info_size, file_info_buffer);

    EFI_FILE_INFO *file_info = (EFI_FILE_INFO *)file_info_buffer;
    UINTN kernel_file_size = file_info->FileSize;

    EFI_PHYSICAL_ADDRESS kernel_base_addr = 0x100000;
    ST->BootServices->AllocatePages(
        AllocateAddress, EfiLoaderData,
        (kernel_file_size + 0xfff) / 0x1000, &kernel_base_addr);
    kernel_file->Read(kernel_file, &kernel_file_size, (VOID *)kernel_base_addr);
    custom_printf("Kernel: 0x%x (%u bytes)\n", kernel_base_addr, kernel_file_size);
    // #@@range_end(read_kernel)

    // #@@range_begin(exit_bs)
    EFI_STATUS status;
    status = ST->BootServices->ExitBootServices(image_handle, memmap.map_key);
    if (EFI_ERROR(status))
    {
        status = GetMemoryMap(&memmap);
        if (EFI_ERROR(status))
        {
            assert(status, L"failed to get memory map:");
            while (1)
                ;
        }
        status = ST->BootServices->ExitBootServices(image_handle, memmap.map_key);
        if (EFI_ERROR(status))
        {
            assert(status, L"Could not exit boot service:");
            while (1)
                ;
        }
    }
    // #@@range_end(exit_bs)

    // #@@range_begin(call_kernel)
    UINT64 entry_addr = *(UINT64 *)(kernel_base_addr + 24);

    typedef void EntryPointType(void);
    EntryPointType *entry_point = (EntryPointType *)entry_addr;
    entry_point();
    // #@@range_end(call_kernel)

    custom_wprintf(L"All done\n");

    while (1)
        ;
    return EFI_SUCCESS;
}