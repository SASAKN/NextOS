/* Neos Boot Loader v0.01 */

#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

/* Entry Point ! */
/* 起動時の最初に実行されます。 */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    char buffer[200];
    text_gen(buffer, sizeof(buffer), "Test: %x", 42);
    zeroPad(buffer, 8);
    custom_printf("%s\n", buffer);
    /* メモリーのバッファーなどを設定 */
    CHAR8 memmap_buf[MEM_DESC_SIZE];
    UINT64 memmap_size = MEM_DESC_SIZE;
    /* メモリーマップ構造体の設定 */
    struct MemoryMap map;
    map.buffer = memmap_buf;
    map.buffer_size = memmap_size;
    /* メモリーの管理をスタート */
    init_memmap(&map);
    print_memmap(&map);
    while (1);
    return EFI_SUCCESS;
};