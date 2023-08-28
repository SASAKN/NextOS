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
    uint64_t (*output_string) (SimpleTextOutputProtocol*, const wchar_t*);
    uint64_t (*test_string) (SimpleTextOutputProtocol*, wchar_t*);
    uint64_t (*query_mode) (SimpleTextOutputProtocol*,
                            wchar_t*,
                            uint64_t* columns,
                            uint64_t* rows);
    uint64_t (*set_mode) (SimpleTextOutputProtocol*, uint64_t);
    uint64_t (*set_attribute) (SimpleTextOutputProtocol*, uint64_t Attribute);
    uint64_t (*clear_screen) (SimpleTextOutputProtocol*);
    uint64_t _buf4[2];
    struct SIMPLE_TEXT_OUTPUT_MODE{
        int MaxMode;
        int Mode;
        int Attribute;
        int CursorColumn;
        int CursorRow;
        uint8_t CursorVisible;
    } * Mode;
} SimpleTextOutputProtocol;

typedef struct {
    uint16_t year;
    uint8_t mon;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t p1;
    uint32_t ns;
    uint16_t tz;
    uint8_t dl;
    uint8_t p2;
} tm;





/* Types Structure */

#endif