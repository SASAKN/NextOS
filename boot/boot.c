/* Neos Boot Loader v0.01 */

#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

/* メモリー用の関数 */
/* NEOSのブート中のメモリー管理 */

struct MemoryMap *mem_map;

EFI_STATUS GetMemoryMap(struct MemoryMap *mem_map) {
    if (mem_map->buffer == NULL) {
        return EFI_BUFFER_TOO_SMALL;
    };
    /* もしエラーを返さないなら */
    init_memmap(mem_map);
}

/* Entry Point ! */
/* 起動時の最初に実行されます。 */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    GetMemoryMap(mem_map);
    print_memmap(mem_map);
    while (1);
    return EFI_SUCCESS;
};