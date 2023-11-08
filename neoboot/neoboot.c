#include "uefi/uefi.h"
#include "include/mem.h"

void PrintOK(void)
{
    ST->ConOut->SetAttribute(ST->ConOut, 0x02); /* 緑で、OKを表示 */
    ST->ConOut->OutputString(ST->ConOut, L"[ OK ]");
    ST->ConOut->SetAttribute(ST->ConOut, 0x0F); /* 白に戻す */
};

void PrintWarn(void)
{
    ST->ConOut->SetAttribute(ST->ConOut, 0x0E); /* 黄色で、Warnを表示 */
    ST->ConOut->OutputString(ST->ConOut, L"[ Warn ]");
    ST->ConOut->SetAttribute(ST->ConOut, 0x0F); /* 白に戻す */
};

void PrintError(void)
{
    ST->ConOut->SetAttribute(ST->ConOut, 0x04); /* あかで、Errorを表示 */
    ST->ConOut->OutputString(ST->ConOut, L"[ Error ! ]");
    ST->ConOut->SetAttribute(ST->ConOut, 0x0F); /* 白に戻す */
};

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
        PrintError();
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
        PrintError();
        fprintf(stderr, "unable to allocate memory. \n");
        while (1)
            __asm__("hlt");
        return 1;
    }
    // 2回目の実行で取得
    status = BS->GetMemoryMap(&map->map_size, (efi_memory_descriptor_t *)map->buffer, &map->map_key, &map->descriptor_size, NULL);
    if (EFI_ERROR(status))
    {
        PrintError();
        fprintf(stderr, "Unable to Get Memory Map !\n");
        while (1)
            __asm__("hlt");
        return 0;
    }
    map->memmap_desc_entry = map->map_size / map->descriptor_size;
    PrintOK();
    printf("Get Memory Map\n");
    return EFI_SUCCESS;
}

efi_status_t print_memmap(struct MemoryMap *map)
{
    efi_status_t status;
    printf("\n[ INFO ] MemoryMap\n");
    printf("Index, Buffer, Type, Type(name),PhysicalStart, VirtualStart, NumberOfPages, Size,  Attribute\n");
    uint32_t i;
    efi_memory_descriptor_t *desc = (efi_memory_descriptor_t *)map->buffer;
    for (i = 0; i < map->memmap_desc_entry; i++)
    {
        printf("%02d, %016x, %02x, %s, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        desc = (efi_memory_descriptor_t *)((uint8_t *)desc + map->descriptor_size);
    }
    PrintOK();
    printf("Print Memory Map\n");
    return 0;
}

efi_status_t save_memmap(struct MemoryMap *map)
{
    FILE *f;
    char *header = "Index, Buffer, Type, Type(name),PhysicalStart, VirtualStart, NumberOfPages, Size,  Attribute\n";
    size_t size;
    efi_memory_descriptor_t *desc = (efi_memory_descriptor_t *)map->buffer;
    if ((f = fopen("\\memmap", "a")))
    {
        //ヘッダーの書き込み
        fprintf(f, "%s", header);
        for (uint32_t i = 0; i < map->memmap_desc_entry; i++)
        {
            fprintf(f, "%02d, %016x, %02x, %s, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
            desc = (efi_memory_descriptor_t *)((uint8_t *)desc + map->descriptor_size);
        }
    }
    fclose(f);
    PrintOK();
    printf("Save Memory Map\n");
    return 0;
}

efi_status_t test_memmap_file(void) {
    FILE *f;
    char_t *buff;
    size_t size;
    if ((f = fopen("\\memmap", "r"))) {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        printf("[ INFO ] File Size : %d bytes.\n", size);
        buff = malloc(size + 1);
        if (!buff) {
            PrintError();
            fprintf(stderr, "unable to allocate memory.\n");
            return 1;
        }
        fread(buff, size, 1, f);
        buff[size] = 0;
        fclose(f);
        // printf("[T]:\n%s\n", buff);
        if (size <= 94) {
            PrintError();
            printf("Save File\n");
        }
        free(buff);
    } else {
        PrintError();
        fprintf(stderr, "unable to open file\n");
        return 0;
    }
    PrintOK();
    printf("Read Memory Map file\n");
    return 0;

}

int main(int argc, char **argv)
{
    // Init UEFI Lib.
    (void)argc;
    (void)argv;
    efi_status_t status;
    // MemoryMap
    PrintOK();
    printf("Welcome to Neo Boot !\n");
    struct MemoryMap map;
    map.map_size = 0;
    map.map_key = 0;
    map.descriptor_size = 0;
    // Get,Print,Save.
    get_memory_map(&map);
    print_memmap(&map);
    save_memmap(&map);
    test_memmap_file();
    // halt cpu.
    while (1)
        __asm__("hlt");
    return EFI_SUCCESS;
}