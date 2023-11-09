#include "uefi/uefi.h"
#include "include/mem.h"
#include "include/stb_image.h"

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

/* ベンダーなどの情報を表示 */
void PrintEfiConfigurationTable(void)
{
    uint64_t i;
    printf("\n[ INFO ] EfiConfigurationTable\n");
    for (i = 0; i < ST->NumberOfTableEntries; i++)
    {
        printf("%02d : %016x : %08x, %04x, %04x\n", i, (unsigned long long)&ST->ConfigurationTable[i], ST->ConfigurationTable[i].VendorGuid.Data1, ST->ConfigurationTable[i].VendorGuid.Data2, ST->ConfigurationTable[i].VendorGuid.Data3);
        unsigned char j;
        for (j = 0; j < 8; j++)
        {
            printf("%02x", ST->ConfigurationTable[i].VendorGuid.Data4[j]);
        }
        printf("%016x\n", (unsigned long long)ST->ConfigurationTable[i].VendorTable);
    }
    PrintOK();
    printf("VendorTable\n");
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
        // ヘッダーの書き込み
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

efi_status_t test_memmap_file(void)
{
    FILE *f;
    char_t *buff;
    size_t size;
    if ((f = fopen("\\memmap", "r")))
    {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        printf("[ INFO ] Memory Map File Size : %d bytes.\n", size);
        buff = malloc(size + 1);
        if (!buff)
        {
            PrintError();
            fprintf(stderr, "unable to allocate memory.\n");
            return 1;
        }
        fread(buff, size, 1, f);
        buff[size] = 0;
        fclose(f);
        // printf("[T]:\n%s\n", buff);
        if (size <= 94)
        {
            PrintError();
            printf("Save File\n");
        }
        free(buff);
    }
    else
    {
        PrintError();
        fprintf(stderr, "unable to open file\n");
        return 0;
    }
    PrintOK();
    printf("Read Memory Map file\n");
    return 0;
}

efi_status_t load_splash(int32_t w, int32_t h, int32_t l, uint32_t *data, unsigned char *buffer)
{
    FILE *f;
    long int size;
    stbi__context s;
    stbi__result_info ri;

    if ((f = fopen("\\splash\\splash.png", "r")))
    {
        // Read Size.
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        // Allocate Buffer
        buffer = (unsigned char *)malloc(size);
        if (!buff)
        {
            PrintError();
            fprintf(stderr, "Unable to allocate memory.\n");
        }
        // Read File
        fread(buff, size, 1, f);
        // Close File
        fclose(f);
        // Decode png image
        ri.bits_per_channel = 8;
        s.read_from_callbacks = 0;
        s.img_buffer = s.img_buffer_original = buff;
        s.img_buffer_end = s.img_buffer_original_end = buff + size;
        data = (uint32_t *)stbi__png_load(&s, &w, &h, &l, 4, &ri);
        if (!data)
        {
            PrintError();
            fprintf(stdout, "Unable to decode png : %s\n", stbi__g_failure_reason);
            return EFI_SUCCESS;
        }
    }
    else
    {
        PrintOK();
        printf("No Splash in folder with bootloader\n");
    }
}

efi_status_t show_splash(efi_gop_t *gop, efi_guid_t *gop_guid, int32_t w, int32_t h, int32_t l, uint32_t *data, unsigned char *buffer)
{
    // set video mode
    efi_status_t status;
    status = BS->LocateProtocol(gop_guid, NULL, (void **)&gop);
    if (!EFI_ERROR(status) && gop)
    {
        status = gop->SetMode(gop, 0);
        ST->ConOut->Reset(ST->ConOut, 0);
        ST->StdErr->Reset(ST->StdErr, 0);
        if (EFI_ERROR(status))
        {
            PrintError();
            fprintf(stderr, "unable to set video mode\n");
            return 0;
        }
    }
    else
    {
        PrintError();
        fprintf(stderr, "unable to get graphics output protocol\n");
        return 0;
    }

    // RGBA to BGRA
    if (gop->Mode->Information->PixelFormat == PixelBlueGreenRedReserved8BitPerColor || (gop->Mode->Information->PixelFormat == PixelBitMask && gop->Mode->Information->PixelInformation.BlueMask != 0xff0000))
    {
        for (l = 0; l < w * h; l++)
        {
            data[l] = ((data[l] & 0xff) << 16) | (data[l] & 0xff00) | ((data[l] >> 16) & 0xff);
        }
    }

    // Display Splash
    gop->Blt(gop, data, EfiBltBufferToVideo, 0, 0, (gop->Mode->Information->HorizontalResolution - w) / 2,
             (gop->Mode->Information->VerticalResolution - h) / 2, w, h, 0);
    free(data);
    free(buffer);
}

int main(int argc, char **argv)
{
    // Init UEFI Lib.
    (void)argc;
    (void)argv;
    efi_status_t status;
    int32_t w, h, l;
    unsigned char *buffer;
    uint32_t data;
    // Graphics
    efi_guid_t gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t *gop = NULL;
    // Reset Watchdog Timer
    ST->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
    // Start
    PrintOK();
    printf("Welcome to Neo Boot !\n");
    // EfiConfigurationTable
    PrintEfiConfigurationTable();
    // MemoryMap
    struct MemoryMap map;
    map.map_size = 0;
    map.map_key = 0;
    map.descriptor_size = 0;
    // Get,Print,Save.
    get_memory_map(&map);
    print_memmap(&map);
    save_memmap(&map);
    test_memmap_file();
    // Load Splash
    load_splash();
    // Show Splash
    show_splash();
    // halt cpu.
    while (1)
        __asm__("hlt");
    return EFI_SUCCESS;
}