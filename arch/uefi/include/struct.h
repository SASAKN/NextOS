#ifndef _UEFI_UEFIDEF_H
#define _UEFI_UEFIDEF_H




/* キーの入力 */

/* EFI_INPUT_KEY */
typedef struct
{
    UINT16 ScanCode;
    UINT16 UnicodeChar;
} EFI_INPUT_KEY;

/* EFI_KEY_OPTION */
typedef struct
{
    EFI_BOOT_KEY_DATA KeyData;
    UINT32 BootOptionCrc;
    UINT16 BootOption;
} EFI_KEY_OPTION;

/* メモリー */

/* EFI_MEMORY_TYPE */
typedef enum
{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

/* EFI_MEMORY_DESCRIPTOR */
typedef struct
{
    UINT32 Type;
    EFI_STATUS PhysicalStart;
    EFI_STATUS VirtualStart;
    EFI_STATUS NumberOfPages;
    EFI_STATUS Attribute;
} EFI_MEMORY_DESCRIPTOR;

/* 時間関係 */

/* EFI_TIME */
typedef struct
{
    UINT16 Year;
    UINT8 Month;
    UINT8 Day;
    UINT8 Hour;
    UINT8 Minute;
    UINT8 Second;
    UINT8 Pad1;
    UINT32 Nanosecond;
    INT16 TimeZone;
    UINT8 Daylight;
    UINT8 Pad2;
} EFI_TIME;

/* EFI_TIMER_DELAY */
typedef enum
{
    TimerCancel,
    TimerPeriodic,
    TimerRelactive
} EFI_TIMER_DELAY;

#endif