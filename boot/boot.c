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
    struct MemoryMap memmap = {sizeof(memmap_buf), memmap_buf, 0, 0, 0, 0};
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    init_memmap(&mem_map);
    // print_memmap(&mem_map);
    while (1);
    return EFI_SUCCESS;
};