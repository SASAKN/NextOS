#ifndef _BOOT_PROTO_H
#define _BOOT_PROTO_H

#include "efi.h"
#include "mem.h"
#include "graphics.h"

/* Boot Proto Defines */
/* EFI */
void efi_init(EFI_SYSTEM_TABLE *SystemTable);
void dump_eficonftable(void);

/* Graphics */
void graphics_init(struct frame_buffer);

/* Common */
void putc (UINT16 c);
void puts(UINT16 *s);
UINT16 getc(void);
UINT32 gets(UINT16 *buf, UINT32 buf_size);
void PrintHex(UINT64 val, UINT8 num_degits); /* 16進数の出力 */
UINT8 check_warn_error (UINT64 status, UINT16 *mess);
UINTN EFIAPI strlen(const CHAR8 *String); /* 文字数を数える */
void assert (UINT64 status, UINT16 *mess);
/* 基本的なテキストの表示 */
int custom_atoi(const char *str);
size_t itoa(char *str, size_t max_size, unsigned int value, int base);
size_t zeroPad(char *input, int width); /* ゼロ埋めの実装 */
void custom_wctomb(wchar_t wc, char* dest, size_t destSize);
void custom_wprintf(const wchar_t *format, ...);
void custom_printf(const char *format, ...);
void text_gen(char *str, size_t max_size, const char *format, ...);
void custom_strcpy(char *dest, const char *src);
void custom_strcat(char *dest, const char *src);
void custom_memmove(void *dest, const void *src, size_t n);
void* custom_memset(void *dst, int c, size_t n); /* メモリーにバイトのセット */
void PrintOK(EFI_SYSTEM_TABLE *SystemTable);
void PrintWarn(EFI_SYSTEM_TABLE *SystemTable);
void PrintError(EFI_SYSTEM_TABLE *SystemTable);
void hex_gen(char *out, UINT64 val, UINT8 num_digits);

/* Memory */
void print_memmap(struct MemoryMap* map);
EFI_STATUS init_memmap(struct MemoryMap *map);
void save_memmap(struct MemoryMap *map, EFI_FILE_PROTOCOL *file);
UINT16 *get_memtype_name(EFI_MEMORY_TYPE type);

#endif