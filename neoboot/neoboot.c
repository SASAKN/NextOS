#include "uefi/uefi.h"
#include "include/mem.h"

char_t *get_memtype_name(efi_memory_type_t type)
{
    switch (type)
    {
    case EfiReservedMemoryType:
        return "EfiReservedMemoryType";
    case EfiLoaderCode:
        return "EfiLoaderCode";
    case EfiLoaderData:
        return "EfiLoaderData";
    case EfiBootServicesCode:
        return "EfiBootServicesCode";
    case EfiBootServicesData:
        return "EfiBootServicesData";
    case EfiRuntimeServicesCode:
        return "EfiRuntimeServicesCode";
    case EfiRuntimeServicesData:
        return "EfiRuntimeServicesData";
    case EfiConventionalMemory:
        return "EfiConventionalMemory";
    case EfiUnusableMemory:
        return "EfiUnusableMemory";
    case EfiACPIReclaimMemory:
        return "EfiACPIReclaimMemory";
    case EfiACPIMemoryNVS:
        return "EfiACPIMemoryNVS";
    case EfiMemoryMappedIO:
        return "EfiMemoryMappedIO";
    case EfiMemoryMappedIOPortSpace:
        return "EfiMemoryMappedIOPortSpace";
    case EfiPalCode:
        return "EfiPalCode";
    case EfiPersistentMemory:
        return "EfiPersistentMemory";
    case EfiMaxMemoryType:
        return "EfiMaxMemoryType";
    default:
        return "InvalidMemoryType";
    }
};

efi_status_t get_memory_map(struct MemoryMap *map)
{
    // 構造体に必要なものを１回目で取得
    efi_status_t status;
    status = BS->GetMemoryMap(&map->map_size, NULL, &map->map_key, &map->descriptor_size, NULL);
    // エラー処理
    if (status != EFI_BUFFER_TOO_SMALL || !map->map_size)
    {
        fprintf(stderr, "Unable to Get Memory Map !\n");
        while (1)
            __asm__("hlt");
        return 0;
    }
    // メモリーマップのサイズの処理
    map->map_size += 4 * map->descriptor_size;
    char_t memmap_buf[map->map_size];
    map->buffer = memmap_buf;
    if (!map->map_size)
    {
        fprintf(stderr, "unable to allocate memory. \n");
        while (1)
            __asm__("hlt");
        return 1;
    }
    // 2回目の実行で取得
    status = BS->GetMemoryMap(&map->map_size, (efi_memory_descriptor_t *)map->buffer, &map->map_key, &map->descriptor_size, NULL);
    if (EFI_ERROR(status))
    {
        fprintf(stderr, "Unable to Get Memory Map !\n");
        while (1)
            __asm__("hlt");
        return 0;
    }
    map->memmap_desc_entry = map->map_size / map->descriptor_size;
    return EFI_SUCCESS;
}

efi_status_t print_memmap(struct MemoryMap *map)
{
    efi_status_t status;
    printf("[ INFO ] MemoryMap\n");
    printf("Index, Buffer, Type, Type(name),PhysicalStart, VirtualStart, NumberOfPages(Size), Attribute\n");
    uint32_t i;
    efi_memory_descriptor_t *desc = (efi_memory_descriptor_t *)map->buffer;
    for (i = 0; i < map->memmap_desc_entry; i++)
    {
        printf("%02d, %016x, %02x, %s, %016x, %016x, %016x, %016x \r\n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->Attribute);
        desc = (efi_memory_descriptor_t *)((uint8_t *)desc + map->descriptor_size);
    }
    return 0;
}

efi_status_t save_memmap(struct MemoryMap *map)
{
    FILE *f;
    char_t buf[4096 * 4];
    size_t size;
        efi_memory_descriptor_t *desc = (efi_memory_descriptor_t *)map->buffer;
    if ((f = fopen("\\memmap", "w")))
    {
        for (uint32_t i = 0; i < map->memmap_desc_entry; i++)
        {
            snprintf(buf, sizeof(buf), "%02d, %016x, %02x, %s, %016x, %016x, %016x, %016x \n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->Attribute);
            printf("[Save Memory Map]%s", buf);
            desc = (efi_memory_descriptor_t *)((uint8_t *)desc + map->descriptor_size);
        }
        size = strlen(buf);
        fwrite(buf, size, 1, f);
    }
    return 0;
}

int main(int argc, char **argv)
{
    // Init UEFI Lib.
    (void)argc;
    (void)argv;
    efi_status_t status;
    // MemoryMap
    printf("Welcome to Neo Boot !");
    struct MemoryMap map;
    map.map_size = 0;
    map.map_key = 0;
    map.descriptor_size = 0;
    // Get,Print,Save.
    get_memory_map(&map);
    print_memmap(&map);
    save_memmap(&map);
    // halt cpu.
    while (1)
        __asm__("hlt");
    return EFI_SUCCESS;
}