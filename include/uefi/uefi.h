/* Uefi Header File */
#ifndef _UEFI_H
#define _UEFI_H

/* Defines */
typedef uint64_t UINTN;
typedef void* Handle;

typedef enum{
    kFalse = 0,
    kTrue = 1
} Boolean;

typedef struct {
    UINTN UINTN_Type;
    Handle Handle_Type;
    enum Boolean Boolean_Type;
} EFI;

typedef enum {
    kSuccess = 0x0,
    kBufferTooSmall = 0x8000000000000005,
    kNotFound = 0x800000000000000E,
} Status;

typedef enum {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} ResetType;

typedef enum {
    kReserved,
    kLoaderCode,
    kLoaderData,
    kBootServicesCode,
    kBootServicesData,
    kRuntimeServicesCode,
    kRuntimeServicesData,
    kConventionalMemory,
    kUnusableMemory,
    kACPIReclaimMemory,
    kACPIMemoryNVS,
    kMemoryMappedIO,
    kMemoryMappedIOPortSpace,
    kPalCode,
    kPersistentMemory,
    kMaxMemoryType
} MemoryType;

typedef enum {
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} TimerDelay;

typedef struct {
    char vendor_guid[16];
    void* vendor_table;
} ConfigurationTable;

typedef struct {
    uint64_t signature;
    uint32_t revision;
    uint32_t header_size;
    uint32_t crc32;
    uint32_t reserved;
} TableHeader;

typedef struct{
   uint16_t ScanCode;
   wchar_t UnicodeChar;
} InputKey;

typedef struct {
    uint64_t _buf;
    uint64_t (*ReadKeyStroke)(struct SimpleTextInputProtocol*, InputKey*);
    void* wait_for_key;
} SimpleTextInputProtocol;

typedef struct {
    uint64_t _buf;
    uint64_t 
} SimpleTextOutputProtocol;

typedef struct {

} SimpleTextOutputProtocol;





/* Types Structure */

#endif