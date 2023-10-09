/* Neos Boot Loader v0.01 */

#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

/* メモリー用の関数 */
/* NEOSのブート中のメモリー管理 */

/* Entry Point ! */
/* 起動時の最初に実行されます。 */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    CHAR8 memmap_buf[MEM_BUFFER_SIZE];
    UINT64 memmap_size = MEM_BUFFER_SIZE;
    struct MemoryMap map;
    map.buffer_size = MEM_BUFFER_SIZE;
    map.buffer = memmap_buf;
    init_memmap(&map);
    print_memmap(&map);
    while (1);
    return EFI_SUCCESS;
};