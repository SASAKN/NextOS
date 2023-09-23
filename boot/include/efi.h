/* UEFI 定義 */
#ifndef _EFI_H
#define _EFI_H

#include "types.h" /* Must be First. */

typedef struct EFI_INPUT_KEY
{
    CHAR16 ScanCode;
    CHAR16 UnicodeChar;
};

typedef struct EFI_GUID
{
    UINT32 Data1;
    CHAR16 Data2;
    CHAR16 Data3;
    BOOLEAN Data4[8];
};

typedef enum EFI_GRAPHICS_PIXEL_FORMAT
{
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
};

typedef enum EFI_LOCATE_SEARCH_TYPE
{
    AllHandles,
    ByRegisterNotify,
    ByProtocol
};

typedef enum EFI_MEMORY_TYPE
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
};

typedef enum EFI_TIMER_DELAY
{
    TimerCancel,
    TimerPeriodic,
    TimerRelactive
};

typedef enum EFI_RESET_TYPE
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
};

typedef struct EFI_DEVICE_PATH_PROTOCOL
{
    BOOLEAN Type;
    BOOLEAN SubType;
    BOOLEAN Length[2];
};

typedef struct EFI_MEMORY_DESCRIPTOR
{
    UINTN Type;
    UINT32 PhysicalStart;
    UINT32 VirtualStart;
    UINT32 NumberOfPages;
    UINT32 Attribute;
};

/* Protocols */

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
    UINT64 _buf;
    UINT64(*ReadKeyStroke)
    (
        EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
        EFI_INPUT_KEY *Key);
    void *WaitForKey;
};

/* EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL用の構造体 */
typedef struct SIMPLE_TEXT_OUTPUT_MODE
{
    INT32 MaxMode;
    INT32 Mode;
    INT32 Attribute;
    INT32 CursorColumn;
    INT32 CursorRow;
    UINT8 CursorVisible;
}

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    UINT64 _buf;
    UINT64(*OutputString)
    (
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT16 *String);
    UINT64(*TextString)
    (
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT16 *String);
    UINT64(*QueryMode)
    (
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT64 ModeNumber,
        UINT64 *Columns,
        UINT64 *Rows);
    UINT64(*SetMode)
    (
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT64 ModeNumber);
    UINT64(*SetAttribute)
    (
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        UINT64 Attribute);
    UINT64(*ClearScreen)
    (
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    UINT64 _buf4[2];
    SIMPLE_TEXT_OUTPUT_MODE *Mode;
};

/* EFI_RUNTIME */
typedef struct EFI_RUNTIME_SERVICES
{
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
typedef struct EFI_BOOT_SERVICES
{
    CHAR8 _buf1[24];
    /* Task Pririty Services */
    UINT64 _buf2[2];
    /* Memory Services */
    UINT64 _buf3[2];
    UINT64(*GetMemoryMap)
    (
        UINT64 *MemoryMapSize,
        EFI_MEMORY_DESCRIPTOR *MemoryMap,
        UINT64 *MapKey,
        UINT64 *DescriptorSize,
        UINT32 *DescriptorVersion);
    UINT64(*AllocatePool)
    (
        EFI_MEMORY_TYPE PoolType,
        UINT64 Size,
        VOID **Buffer);
    UINT64(*FreePool)
    (
        VOID *Buffer);
    /* Event & Timer Services */
    UINT64(*CreateEvent)
    (
        UINT32 Type,
        UINT64 NotifyTpl,
        VOID (*NotifyFunction)(VOID *Event, VOID *Context),
        VOID *NotifyContext,
        VOID *Event);
    UINT64(*SetTimer)
    (VOID *Event,
     EFI_TIMER_DELAY Type,
     UINT64 TriggerTime);
    UINT64(*WaitForEvent)
    (
        UINT64 NumberOfEvents,
        VOID **Event,
        UINT64 *Index);
    UINT64 _buf4_2[3];
    /* Protocol Handler Services */
    UINT64 _buf5[3];
    UINT64(*HandleProtocol)
    (VOID *Handle,
     EFI_GUID *Protocol,
     VOID **Interface);
    UINT64 _buf5_2[5];
    /* Image Services */
    UINT64(*LoadImage)
    (
        UINT8 BootPolicy,
        VOID *ParentImageHandle,
        EFI_DEVICE_PATH_PROTOCOL *DevicePath,
        VOID *SourceBuffer,
        UINT64 SourceSize,
        VOID **ImageHandle);
    UINT64(*StartImage)
    (
        VOID *ImageHandle,
        UINT64 *ExitDataSize,
        UINT16 **ExitData);
    UINT64 _buf6[2];
    UINT64(*ExitBootServices)
    (
        VOID *ImageHandle,
        UINT64 MapKey);
    /* Miscellaneous Services */
    UINT64 _buf7[2];
    UINT64(*SetWatchdogTimer)
    (
        UINT64 TimeOut,
        UINT64 WatchdogCode,
        UINT64 DataSize,
        CHAR16 *WatchdogData);
    /* DriverSupportServices */
    UINT64 _buf8[2];
    /* Open & Close Protocol Services */
    UINT64(*OpenProtocol)
    (
        VOID *Handle,
        EFI_GUID *Protocol,
        VOID **Interface,
        VOID *AgentHandle,
        VOID *ControllerHandle,
        UINT32 Attributes);
    UINT64 _buf9[2];
    /* Library Services */
    UINT64 _buf10;
    UINT64(*LocateHandleBuffer)
    (
        EFI_LOCATE_SEARCH_TYPE SearchType,
        EFI_GUID *Protocol,
        VOID *SearchKey,
        UINT64 *NoHandles,
        VOID ***Buffer);
    UINT64(*LocateProtocol)
    (
        EFI_GUID *Protocol,
        VOID *Registration,
        VOID **Interface);
    UINT64 _buf10_2[2];
    /* 32bit CRC Services */
    UINT64 _buf11;
    /* Miscellaneous Services */
    VOID(*CopyMem)
    (
        VOID *Destination,
        VOID *Source,
        UINT64 Length);
    VOID(*SetMem)
    (
        VOID *Buffer,
        UINT64 Size,
        UINT8 Value);
    UINT64 _buf12;
};

typedef struct EFI_CONFIGURATION_TABLE
{
    EFI_GUID VendorGuid;
    VOID *VendorTable;
};

/* EFI_SYSTEM_TABLE */
typedef struct EFI_SYSTEM_TABLE
{
    CHAR8 _buf1[44];
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    UINT64 _buf2;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    UINT64 _buf3[2];
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINT64 NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigurationTable;
};

/* Graphics Output Protocol 用の定義 */

/* 加法混色 */
typedef struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL
{
    UINT8 Blue;
    UINT8 Green;
    UINT8 Red;
    UINT8 Reserved;
};

typedef struct EFI_GRAPHICS_OUTPUT_MODE_INFOMATION
{
    UINT32 Version;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
}

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE
{
    UINT32 MaxMode;
    UINT32 Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFOMATION *Info;
    UINT64 SizeOfInfo;
    UINT64 FrameBufferBase;
    UINT64 FrameBufferSize;
};

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL
{
    UINT64 _buf[3];
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
};

typedef struct EFI_SIMPLE_POINTER_STATE
{
    INT32 RelactiveMovementX;
    INT32 RelactiveMovementY;
    INT32 RelactiveMovementZ;
    UINT8 LeftButton;
    UINT8 RightButton;
};

typedef struct EFI_SIMPLE_POINTER_PROTOCOL
{
    UINT64(*Reset)
    (
        EFI_SIMPLE_POINTER_PROTOCOL *This,
        UINT8 ExtendedVerification);
    UINT64(*GetState)
    (
        EFI_SIMPLE_POINTER_PROTOCOL *This,
        EFI_SIMPLE_POINTER_STATE *State);
    VOID *WaitForInput;
};

typedef struct EFI_TIME
{
    UINT16 Year;
    UINT8 Month;
    UINT8 Day;
    UINT8 Hour;
    UINT8 Minute;
    UINT8 Second;
    UINT8 Pad1;
    UINT32 Nanosecond;
    UINT16 TimeZone;
    UINT8 Daylight;
    UINT8 Pad2;
};

typedef struct EFI_FILE_INFO
{
    UINT64 Size;
    UINT64 FileSize;
    UINT64 PhysicalSize;
    EFI_TIME CreateTime;
    EFI_TIME LastAccessTime;
    EFI_TIME ModificationTime;
    UINT64 Attribute;
    UINT16 FileName[];
};

typedef struct EFI_FILE_PROTOCOL
{
    UINT64 _buf;
    UINT64(*Open)
    (EFI_FILE_PROTOCOL *This,
     EFI_FILE_PROTOCOL **NewHandle,
     UINT16 *FileName,
     UINT64 OpenMode,
     UINT64 Attributes);
    UINT64(*Close)
    (EFI_FILE_PROTOCOL *This);
    UINT64 _buf2;
    UINT64(*Read)
    (EFI_FILE_PROTOCOL *This,
     UINT64 *BufferSize,
     VOID *Buffer);
    UINT64(*Write)
    (EFI_FILE_PROTOCOL *This,
     UINT64 *BufferSize,
     VOID *Buffer);
    UINT64 _buf3[2];
    UINT64(*GetInfo)
    (EFI_FILE_PROTOCOL *This,
     EFI_GUID *InfomationType,
     UINT64 *BufferSize,
     VOID *Buffer);
    UINT64 _buf4;
    UINT64(*Flush)
    (EFI_FILE_PROTOCOL *This);
};

typedef struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL
{
    UINT64 Revision;
    UINT64(*OpenVolume)
    (
        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
        EFI_FILE_PROTOCOL **Root);
};

typedef struct EFI_KEY_STATE
{
    UINT32 KeyShiftState;
    UINT8 KeyToggleState;
};

typedef struct EFI_KEY_DATA
{
    EFI_INPUT_KEY Key;
    EFI_KEY_STATE KeyState;
};

typedef struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
{
    UINT64(*Reset)
    (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
     UINT8 ExtendedVerifiation);
    UINT64(*ReadKeyStrokeEx)
    (
        EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        EFI_KEY_DATA *KeyData);
    VOID *WaitForKeyEx;
    UINT64(*SetState)
    (
        EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        UINT8 *KeyToggleState);
    UINT64(*RegisterKeyNotify)
    (
        EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        EFI_KEY_DATA *KeyData,
        UINT64 (*KeyNotificationFunction)(
            EFI_KEY_DAA *KeyData),
        VOID *NottificationHandle);
    UINT64(*UnRegisterKeyNotify)
    (
        EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        VOID *NotificationHandle);
};

typedef struct EFI_LOADED_IMAGE_PROTOCOL
{
    UINT32 Revision;
    VOID *ParentHandle;
    EFI_SYSTEM_TABLE *SystemTable;
    VOID *DeviceHandle;
    EFI_DEVICE_PATH_PROTOCOL *FilePath;
    VOID *Reserved;
    UINT32 LoadOptions Size;
    VOID *LoadOptions;
    VOID *ImageBase;
    UINT64 ImageSize;
    EFI_MEMORY_TYPE ImageCodeType;
    EFI_MEMORY_TYPE ImageDataType;
    UINT64(*Unload)
    (VOID *ImageHandle);
};

typedef struct EFI_DEVICE_PATH_TO_TEXT_PROTOCOL
{
    EFI_DEVICE_PATH_PROTOCOL *(*ConvertTextToDeviceNode)(
        const unsigned short *TextDeviceNode);
    EFI_DEVICE_PATH_PROTOCOL *(*ConvertTextToDevicePath)(
        const unsigned short *TextDevicePath);
};

typedef struct EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL
{
    EFI_DEVICE_PATH_PROTOCOL *(*ConvertTextToDeviceNode)(
        const UINT16 *TextDeviceNode);
    EFI_DEVICE_PATH_PROTOCOL *(*ConvertTextToDevicePath)(
        const UINT16 *TextDevicePath);
}

typedef struct EFI_DEVICE_PATH_UTILITIES_PROTOCOL
{
    UINT64 _buf[3];
    EFI_DEVICE_PATH_PROTOCOL *(*AppendDeviceNode)(
        const EFI_DEVICE_PATH_PROTOCOL *DevicePath,
        const EFI_DEVICE_PATH_PROTOCOL *DeviceNode);
};

typedef struct EFI_CPU_PHYSICAL_LOCATION
{
    UINT32 Package;
    UINT32 Core;
    UINT32 Thread;
};

typedef struct EFI_PROCESSOR_INFOMATION
{
    UINT64 ProcessorId;
    UINT32 StatusFlag;
    EFI_CPU_PHYSICAL_LOCATION Location;
};

typedef struct EFI_MP_SERVICES_PROTOCOL
{
    UINT64(*GetNumberOfProcessors)
    (
        EFI_MP_SERVICES_PROTOCOL *This,
        UINT64 *NumberOfProcessors,
        UINT64 *NumberOfEnabledProcessors);
    UINT64(*GetProcessorInfo)
    (
        EFI_MP_SERVICES_PROTOCOL *This,
        UINT64 ProcessorNumber,
        EFI_PROCESSOR_INFOMATION *ProcessorInfoBuffer);
    UINT64(*StartupAllAPs)
    (
        EFI_MP_SERVICES_PROTOCOL *This,
        VOID (*Procedure)(VOID *ProcedureArgument),
        UINT8 SingleThread;
        VOID * WaitEvent,
        UINT64 TimeoutInMicroSeconds,
        VOID *ProcudureArgument,
        UINT64 **FailedCpuList);
    UINT64(*StartuphisAP)
    (
        EFI_MP_SERVICES_PROTOCOL *This,
        VOID (*Procudure)(VOID *ProcedureArgument),
        UINT64 ProcessorNumber,
        VOID *WaitEvent,
        UINT64 TimeoutInMicroseconds,
        VOID *ProcedureArgument,
        UINT8 *Finished);
    UINT64(*SwitchBSP)
    (
        EFI_MP_SERVICES_PROTOCOL *This,
        UINT64 ProcessorNumber,
        UINT8 EnableOldBSP);
    UINT64(*EnableDisableAP)
    (
        EFI_MP_SERVICES_PROTOCOL *This,
        UINT64 ProcessorNumber,
        UINT8 EnableAP,
        UINT32 *HealthFlag);
    UINT64(*WhoAmI)
    (
        EFI_MP_SERVICES_PROTOCOL *This,
        UINT64 *ProcessorNumber);
};

extern EFI_SYSTEM_TABLE *ST;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
extern EFI_SIMPLE_POINTER_PROTOCOL *SPP;
extern EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFSP;
extern EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *STIEP;
extern EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *DPTTP;
extern EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *DPFTP;
extern EFI_DEVICE_PATH_UTILITIES_PROTOCOL *DPUP;
extern EFI_MP_SERVICES_PROTOCOL *MSP;
extern EFI_GUID lip_guid;
extern EFI_GUID dpp_guid;
extern EFI_GUID fi_guid;
extern EFI_GUID sfsp_guid;

/* EFI PROTOTYPE */
void efi_init(EFI_SYSTEM_TABLE *SystemTable);
void dump_eficonftable(void);
void *find_efi_acpi_table(void);

#endif