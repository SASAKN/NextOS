/* Uefi Header File */
#ifndef _UEFI_H
#define _UEFI_H

/* Defines */
typedef uint64_t UINTN;
typedef void* Handle;
typedef uint64_t Status;  // Status の再定義
typedef uint64_t AllocateType;  // AllocateType の再定義
typedef uint64_t TimerDelay; 
typedef uint64_t TimerTick;  

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
    uint16_t Year;
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minuite;
    uint8_t Second;
    uint8_t Pad1;
    uint32_t Nanosecond;
    uint16_t TimeZone;
    uint8_t Daylight;
    uint8_t Pad2;
} Time;

const kFileNameSize = 32;

typedef struct {
    uint64_t size;
    uint64_t file_size;
    uint64_t physical_size;
    Time  create_time;
    Time last_access_time;
    Time modification_time;
    uint64_t attr;
    wchar_t file_name[kFileNameSize];
} FileInfo;

const int kVolumeLabelSize = 32;

typedef struct {
    uint64_t size;
    Boolean readonly;
    uint64_t volume_size;
    uint64_t free_space;
    uint64_t block_size;
    wchar_t volume_label[kVolumeLabelSize];
} FileSystemInfo;

typedef enum {
    kRead = 1,
} FileProrocolModes;

typedef struct {
    uint64_t revision;
    Status (*Open)(FileProtocol* self, FileProtocol** new_handle, const wchar_t* rel_path, FileProtocolModes mode, uint64_t attr);
    Status (*Close)(FileProtocol* self);
    Status (*Delete)(FileProtocol* self);
    Status (*Read)(FileProtocol* self, UINTN* buffer_size, void* buffer);
    uint64_t (*Write)(FileProtocol* self);
    uint64_t _buf3[2];
    Status (*GetInfo)(FileProtocol* self, const GUID* type, UINTN* buffer_size, uint8_t* buffer);
    uint64_t _buf4;
    Status (*Flush)(FileProtocol* self);
} FileProtocol;

typedef struct {
    uint64_t Revision;
    Status (*OpenVolume)(SimpleFileSystemProtocol* self, FileProtocol** Root);
};

typedef struct {
    char _buf_rs1[24];
    uint64_t _buf_rs2[4];
    uint64_t _buf_rs3[2];
    uint64_t _buf_rs4[3];
    uint64_t _buf_rs5;
    void (*reset_system)(ResetType,
                        uint64_t reset_status,
                        uint64_t data_size,
                        void*);
} RuntimeServices;

typedef struct {
    MemoryType type;
    uint64_t physical_start;
    uint64_t virtual_start;
    uint64_t number_of_pages;
    uint64_t attribute;
} MemoryDescriptor;

void PrintMemoryDescriptor(const MemoryDescriptor* descriptor);

typedef struct {
    unsigned char Type;
    unsigned char SubType;
    unsigned char Length[2];
} DevicePathProtocol;

typedef enum {
    kAnyPages,
    kMaxAddress,
    kAddress,
} AllocateType;

typedef struct {
    char _buf1[24];
    Status (*RaiseTPL)();
    Status (*RestoreTPL)();
    Status (*AllocatePages)(AllocateType, MemoryType, UINTN pages, void** mem);
    Status (*FreePages)();
    Status (*GetMemoryMap)(UINTN* memory_map_size, uint8_t*, UINTN* map_key, UINTN* descriptor_size, uint32_t descriptor_version);
    uint64_t (*AllocatePool)(MemoryType, uint64_t, void**);
    uint64_t (*FreePool)(void* Buffer);
    uint64_t (*CreateEvent)(unsigned int Type, uint64_t NotifyTpl, void (*NotifyFunction)(void* Event, void* Context), void* NotifyContext, void* Event);
    uint64_t (*SetTimer)(void* Event, TimerDelay, TimerTick);
    uint64_t ()
} BootServices;







/* Types Structure */

#endif