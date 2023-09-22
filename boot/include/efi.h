/* UEFI 定義 */
#ifndef _EFI_H
#define _EFI_H

/* IN OUT  何も意味は、ない*/
#define IN
#define OUT
#define OPTIONAL

/* EFIAPI */
#define EFIAPI

/* Data Types */
typedef unsigned char BOOLEAN;
typedef signed long long INTN;
typedef unsigned long long UINTN;
typedef signed char INT8;
typedef unsigned char UINT8;
typedef short INT16;
typedef unsigned short UINT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef char CHAR8;
typedef unsigned short CHAR16;
typedef void VOID;
typedef unsigned long long EFI_STATUS;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

typedef struct EFI_INPUT_KEY {
    CHAR16 ScanCode;
    CHAR16 UnicodeChar;
};

typedef struct EFI_GUID {
    UINT32 Data1;
    CHAR16 Data2;
    CHAR16 Data3;
    BOOLEAN Data4[8];
};

typedef enum EFI_MEMORY_TYPE {
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
};

typedef enum EFI_TIMER_DELAY {
    TimerCancel,
    TimerPeriodic,
    TimerRelactive
};

typedef enum EFI_RESET_TYPE {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
};

typedef struct EFI_DEVICE_PATH_PROTOCOL {
    BOOLEAN Type;
    BOOLEAN SubType;
    BOOLEAN Length[2];
};

typedef struct EFI_MEMORY_DESCRIPTOR {
    UINTN Type;
    UINT32 PhysicalStart;
    UINT32 VirtualStart;
    UINT32 NumberOfPages;
    UINT32 Attribute;
};

typedef enum EFI_LOCATE_SEARCH_TYPE {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
};

/* Protocols */

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL{
    UINT64 _buf;
    UINT64 (*ReadKeyStroke)(
        struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
        struct EFI_INPUT_KEY *Key);
    void *WaitForKey;
};

/* EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL用の構造体 */
typedef struct SIMPLE_TEXT_OUTPUT_MODE{
    INT32 MaxMode;
    INT32 Mode;
    INT32 Attribute;
    INT32 CursorColumn;
    INT32 CursorRow;
    UINT8 CursorVisible;
}

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    UINT64 _buf;
    UINT64 (*OutputString)(
        struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT16 *String);
    UINT64 (*TextString)(
        struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT16 *String);
    UINT64 (*QueryMode)(
        struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT64 ModeNumber,
        UINT64 *Columns,
        UINT64 *Rows);
    UINT64 (*SetMode)(
        struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT64 ModeNumber);
    UINT64 (*SetAttribute)(
        struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT64 Attribute);
    UINT64 (*ClearScreen)(
        struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    UINT64 _buf4[2];
    SIMPLE_TEXT_OUTPUT_MODE *Mode;
};

/* EFI_RUNTIME */
typedef struct EFI_RUNTIME_SERVICES {
    CHAR8 _buf_rs1[24];
    /* Time Services */
    UINT64 _buf_rs2[4];
    /* Virtual Memory Services */
    UINT64 _buf_rs3[2];
    /* Variable Services */
    UINT64 _buf_rs4[3];
    /* Miscellaneous Services */
    UINT64 _buf_rs5;
    void (*ResetSystem)(EFI_RESET_TYPE ResetType,
            UINT64 ResetStatus,
            UINT64 DataSize,
            VOID *ResetData);
};

/* EFI_BOOT_SERVICES */
typedef struct EFI_BOOT_SERVICES {
    CHAR8 _buf1[24];
    /* Task Pririty Services */
    UINT64 _buf2[2];
    /* Memory Services */
    UINT64 _buf3[2];
    UINT64 (*GetMemoryMap)(
        UINT64 *MemoryMapSize,
        EFI_MEMORY_DESCRIPTOR *MemoryMap,
        UINT64 *MapKey,
        UINT64 *DescriptorSize,
        UINT32 *DescriptorVersion);
    UINT64 (*AllocatePool)(
        EFI_MEMORY_TYPE PoolType,
        UINT64 Size,
        VOID **Buffer);
    UINT64 (*FreePool)(
        VOID *Buffer);
    /* Event & Timer Services */
    UINT64 (*CreateEvent)(
        UINT32 Type,
        UINT64 NotifyTpl,
        VOID (*NotifyFunction)(VOID *Event, VOID *Context),
        VOID *NotifyContext,
        VOID *Event);
    UINT64 (*SetTimer)(VOID *Event,
            EFI_TIMER_DELAY Type,
            UINT64 TriggerTime);
    UINT64 (*WaitForEvent)(
        UINT64 NumberOfEvents,
        VOID ** Event,
        UINT64 *Index);
    UINT64 _buf4_2[3];
    /* Protocol Handler Services */
    UINT64 _buf5[3];
    UINT64 (*HandleProtocol)(VOID * Handle,
            EFI_GUID *Protocol,
            VOID **Interface);
    UINT64 _buf5_2[5];
    /* Image Services */
    UINT64 (*LoadImage)(
        UINT8 BootPolicy,
        VOID *ParentImageHandle,
        EFI_DEVICE_PATH_PROTOCOL *DevicePath,
        VOID *SourceBuffer,
        UINT64 SourceSize,
        VOID **ImageHandle);
    UINT64 (*StartImage)(
        VOID *ImageHandle,
        UINT64 *ExitDataSize,
        UINT16 **ExitData);
    UINT64 _buf6[2];
    UINT64 (*ExitBootServices)(
        VOID *ImageHandle,
        UINT64 MapKey);
    /* Miscellaneous Services */
    UINT64 _buf7[2];
    UINT64 (*SetWatchdogTimer)(
        UINT64 TimeOut,
        UINT64 WatchdogCode,
        UINT64 DataSize,
        CHAR16 *WatchdogData);
    /* DriverSupportServices */
    UINT64 _buf8[2];
    /* Open & Close Protocol Services */
    UINT64 (*OpenProtocol)(
        VOID *Handle,
        EFI_GUID *Protocol,
        VOID **Interface,
        VOID *AgentHandle,
        VOID * ControllerHandle,
        UINT32 Attributes);
    UINT64 _buf9[2];
    /* Library Services */
    UINT64 _buf10;
    UINT64 (*LocateHandleBuffer)(
        EFI_LOCATE_SEARCH_TYPE SearchType,
        EFI_GUID *Protocol,
        VOID *SearchKey,
        UINT64 *NoHandles,
        VOID ***Buffer);
    UINT64 (*LocateProtocol)(
        EFI_GUID *Protocol,
        VOID *Registration,
        VOID **Interface);
    UINT64 _buf10_2[2];
    /* 32bit CRC Services */
    UINT64 _buf11;
    /* Miscellaneous Services */
    VOID (*CopyMem)(
        VOID *Destination,
        VOID *Source,
        UINT64 Length);
    VOID (*SetMem)(
        VOID *Buffer,
        UINT64 Size,
        UINT8 Value);
    UINT64 _buf12;
};

typedef struct EFI_CONFIGURATION_TABLE {
    EFI_GUID VendorGuid;
    VOID *VendorTable;
};







#endif