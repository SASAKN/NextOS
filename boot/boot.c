/* Neos Boot Loader v0.1 */

#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

/* メモリーマップをUEFIファームフェアからブートローダーへ受け渡す */
EFI_STATUS GetMemoryMap(struct MemoryMap* mem_map)
{
    if (mem_map->buffer == NULL)
    {
        return EFI_BUFFER_TOO_SMALL; /* エラーを返す。 */
    };

    mem_map->map_size = mem_map->buffer_size;
    return BS->GetMemoryMap(&mem_map->map_size, (EFI_MEMORY_DESCRIPTOR *)mem_map->buffer, &mem_map->map_key, &mem_map->descriptor_size, &mem_map->descriptor_version);
};

/* メモリーの詳細を画面に表示 */
EFI_STATUS PrintMemoryMap(struct MemoryMap* mem_map) {
    EFI_STATUS status;
    CHAR8 buf[256];
    UINTN len;
    if(EFI_ERROR(status)) {
        return status;
    };

    puts(L"mem_map->buffer = %08lx, mem_map->map_size = %08lx\n");
    puts(mem_map->buffer);
    puts(mem_map->map_size);

}


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