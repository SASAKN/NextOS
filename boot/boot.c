/* Neos Boot Loader v0.1 */

#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

/* メモリーマップをUEFIファームフェアからブートローダーへ受け渡す */
EFI_STATUS GetMemoryMap(struct MemoryMap *map)
{
    if (map->buffer == NULL)
    {
        return EFI_BUFFER_TOO_SMALL; /* エラーを返す。 */
    };

    map->map_size = map->buffer_size;
    return BS->GetMemoryMap(&map->map_size, (EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key, &map->descriptor_size, &map->descriptor_version);
};



/* Entry Point ! */
/* 起動時の最初に実行されます。 */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    puts(L"Hello !");
    while (1)
        ;
    return EFI_SUCCESS;
};