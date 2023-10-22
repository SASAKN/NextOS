#ifndef _EFI_BASE_H
#define _EFI_BASE_H


typedef struct
{
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
} EFI_GUID;

typedef enum
{
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef struct {
 INT32                  RelativeMovementX;
 INT32                  RelativeMovementY;
 INT32                  RelativeMovementZ;
 BOOLEAN                LeftButton;
 BOOLEAN                RightButton;
} EFI_SIMPLE_POINTER_STATE;

typedef struct {
 UINT64                    ResolutionX;
 UINT64                    ResolutionY;
 UINT64                    ResolutionZ;
 BOOLEAN                   LeftButton;
 BOOLEAN                   RightButton;
} EFI_SIMPLE_POINTER_MODE;

typedef struct {
 INT32                              MaxMode;
 INT32                              Mode;
 INT32                              Attribute;
 INT32                              CursorColumn;
 INT32                              CursorRow;
 BOOLEAN                            CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef struct {
 UINT16                             ScanCode;
 CHAR16                             UnicodeChar;
} EFI_INPUT_KEY;

typedef struct EFI_KEY_STATE {
 UINT32                       KeyShiftState;
 EFI_KEY_TOGGLE_STATE         KeyToggleState;
} EFI_KEY_STATE;

typedef struct {
 EFI_INPUT_KEY           Key;
 EFI_KEY_STATE           KeyState;
} EFI_KEY_DATA;

struct EFI_HII_PACKAGE_LIST_HEADER
{
    EFI_GUID PackageListGuid;
    UINT32 PackagLength;
};

typedef struct
{
    UINT16 Year;  // 1900 - 9999
    UINT8 Month;  // 1 - 12
    UINT8 Day;    // 1 - 31
    UINT8 Hour;   // 0 - 23
    UINT8 Minute; // 0 - 59
    UINT8 Second; // 0 - 59
    UINT8 Pad1;
    UINT32 Nanosecond; // 0 - 999,999,999
    INT16 TimeZone;    // —1440 to 1440 or 2047
    UINT8 Daylight;
    UINT8 Pad2;
} EFI_TIME;

typedef struct
{
    UINT32 Resolution;
    UINT32 Accuracy;
    BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef struct
{
    UINT8 Type;
    UINT32 IdSize;
    // UINT8       Id[IdSize];
} EFI_VARIABLE_AUTHENTICATION_3_CERT_ID;

typedef struct
{
    UINT32 NonceSize;
    // UINT8 Nonce[NonceSize];
} EFI_VARIABLE_AUTHENTICATION_3_NONCE;

typedef struct
{
    UINT64 MonotonicCount;
    WIN_CERTIFICATE_UEFI_GUID AuthInfo;
} EFI_VARIABLE_AUTHENTICATION;

typedef struct
{
    EFI_TIME TimeStamp;
    WIN_CERTIFICATE_UEFI_GUID AuthInfo;
} EFI_VARIABLE_AUTHENTICATION_2;

typedef struct
{
    UINT8 Version;
    UINT8 Type;
    UINT32 MetadataSize;
    UINT32 Flags;
} EFI_VARIABLE_AUTHENTICATION_3;

typedef struct
{
    EFI_HANDLE AgentHandle;
    EFI_HANDLE ControllerHandle;
    UINT32 Attributes;
    UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef struct _EFI_DEVICE_PATH_PROTOCOL
{
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef enum
{
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef enum
{
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef struct
{
    EFI_PHYSICAL_ADDRESS Address;
    UINT64 Length;
} EFI_MEMORY_RANGE;

typedef struct
{
    UINT64 FirmwareMemoryRequirement;
    UINT64 NumberOfMemoryRanges;
} EFI_MEMORY_RANGE_CAPSULE_RESULT;

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
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef struct
{
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef enum
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown
        EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef struct
{
    EFI_GUID CapsuleGuid;
    UINT32 HeaderSize;
    UINT32 Flags;
    UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef struct
{
    EFI_CAPSULE_HEADER Header;
    UINT32 OsRequestedMemoryType;
    UINT64 NumberOfMemoryRanges;
    EFI_MEMORY_RANGE MemoryRanges[];
} EFI_MEMORY_RANGE_CAPSULE;

typedef struct
{
    UINT16 Version;
    UINT8 PayloadIndex;
    UINT8 UpdateImageIndex;

    EFI_GUID UpdateImageTypeId;
    // CHAR16            CapsuleFileName [];
    // CHAR16            CapsuleTarget [];
} EFI_CAPSULE_RESULT_VARIABLE_FMP;

typedef struct
{
    UINT32 Version;
    UINT32 CapsuleId;
    UINT32 RespLength;
    UINT8 Resp[];
} EFI_CAPSULE_RESULT_VARIABLE_JSON;

typedef struct
{
    UINT32 CapsuleArrayNumber;
    VOID *CapsulePtr[1];
} EFI_CAPSULE_TABLE;

typedef struct
{
    UINT32 VariableTotalSize;
    UINT32 Reserved; // for alignment
    EFI_GUID CapsuleGuid;
    EFI_TIME CapsuleProcessed;
    EFI_STATUS CapsuleStatus;
} EFI_CAPSULE_RESULT_VARIABLE_HEADER;

typedef struct
{
    UINT64 Length;
    union
    {
        EFI_PHYSICAL_ADDRESS DataBlock;
        EFI_PHYSICAL_ADDRESS ContinuationPointer;
    } Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct _EFI_LOAD_OPTION
{
    UINT32 Attributes;
    UINT16 FilePathListLength;
} EFI_LOAD_OPTION;

typedef struct _EFI_KEY_OPTION
{
    EFI_BOOT_KEY_DATA KeyData;
    UINT32 BootOptionCrc;
    UINT16 BootOption;
} EFI_KEY_OPTION;

typedef enum
{
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} EFI_TIMER_DELAY;

typedef struct
{
    EFI_GUID VendorGuid;
    VOID *VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef union
{
    struct
    {
        UINT32 Revision : 8;
        UINT32 ShiftPressed : 1;
        UINT32 ControlPressed : 1;
        UINT32 AltPressed : 1;
        UINT32 LogoPressed : 1;
        UINT32 MenuPressed : 1;
        UINT32 SysReqPressed : 1;
        UINT32 Reserved : 16;
        UINT32 InputKeyCount : 2;
    } Options;
    UINT32 PackedValue;
} EFI_BOOT_KEY_DATA;

/* EFI_TABLE_HEADER */
typedef struct
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

/* EFI_RT_PROPERTIES_TABLE */
typedef struct
{
    UINT16 Version;
    UINT16 Length;
    UINT32 RuntimeServicesSupported;
} EFI_RT_PROPERTIES_TABLE;

/* EFI_PROPERTIES_TABLE */
typedef struct
{
    UINT32 Version;
    UINT32 Length;
    UINT64 MemoryProtectionAttribute;
} EFI_PROPERTIES_TABLE;

/* EFI_MEMORY_ATTRIBUTES_TABLE */
typedef struct
{
    UINT32 Version;
    UINT32 NumberOfEntries;
    UINT32 DescriptorSize;
    UINT32 Flags;
} EFI_MEMORY_ATTRIBUTES_TABLE;

#endif