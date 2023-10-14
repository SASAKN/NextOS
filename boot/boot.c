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
    /* メモリー関連 */
    CHAR8 memmap_buf[MEM_DESC_SIZE];
    UINT64 memmap_size = MEM_DESC_SIZE;
    struct MemoryMap map;
    map.buffer = memmap_buf;
    map.buffer_size = memmap_size;
    init_memmap(&map);
    print_memmap(&map);
    while (1);
    return EFI_SUCCESS;
};