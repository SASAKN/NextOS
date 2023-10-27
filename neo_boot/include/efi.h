#ifndef _EFI_H
#define _EFI_H

#include "types.h"

typedef struct _EFI_INPUT_KEY
{
    UINT16 ScanCode;
    CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef struct _EFI_GUID
{
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
} EFI_GUID;

/* EFI_PROPERTIES_TABLE */
typedef struct
{
    UINT32 Version;
    UINT32 Length;
    UINT64 MemoryProtectionAttribute;
} EFI_PROPERTIES_TABLE;

typedef struct _EFI_LOAD_OPTION
{
    UINT32 Attributes;
    UINT16 FilePathListLength;
} EFI_LOAD_OPTION;

typedef union _EFI_BOOT_KEY_DATA
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

typedef struct _EFI_KEY_OPTION
{
    EFI_BOOT_KEY_DATA KeyData;
    UINT32 BootOptionCrc;
    UINT16 BootOption;
} EFI_KEY_OPTION;

typedef enum _EFI_INTERFACE_TYPE
{
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef struct _EFI_KEY_STATE
{
    UINT32 KeyShiftState;
    EFI_KEY_TOGGLE_STATE KeyToggleState;
} EFI_KEY_STATE;

typedef struct _EFI_KEY_DATA
{
    EFI_INPUT_KEY Key;
    EFI_KEY_STATE KeyState;
} EFI_KEY_DATA;

typedef enum _EFI_LOCATE_SEARCH_TYPE
{
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef enum _EFI_MEMORY_TYPE
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

typedef enum _EFI_ALLOCATE_TYPE
{
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef struct
{
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef struct
{
    UINT32 Version;
    UINT32 NumberOfEntries;
    UINT32 DescriptorSize;
    UINT32 Flags;
} EFI_MEMORY_ATTRIBUTES_TABLE;

typedef enum
{
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} EFI_TIMER_DELAY;

typedef enum
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef struct _EFI_CONFIGURATION_TABLE
{
    EFI_GUID VendorGuid;
    VOID *VendorTable;
} EFI_CONFIGURATION_TABLE;

/* EFI_RT_PROPERTIES_TABLE */
typedef struct
{
    UINT16 Version;
    UINT16 Length;
    UINT32 RuntimeServicesSupported;
} EFI_RT_PROPERTIES_TABLE;

/* EFI_TABLE_HEADER */
typedef struct _EFI_TABLE_HEADER
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef struct _EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
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

/* SimpleTextProtocol */

typedef EFI_STATUS(EFIAPI *EFI_KEY_NOTIFY_FUNCTION)(
    IN EFI_KEY_DATA *KeyData);

/* EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL */

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
{
    EFI_STATUS(*Reset)
    (
        IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        IN BOOLEAN ExtendedVerification);
    EFI_STATUS(*EFI_INPUT_READ_KEY_EX)
    (
        IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        OUT EFI_KEY_DATA *KeyData);
    EFI_EVENT WaitForKeyEx;
    EFI_STATUS(*SetState)
    (
        IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        IN EFI_KEY_TOGGLE_STATE *KeyToggleState);
    EFI_STATUS(*EFI_REGISTER_KEYSTROKE_NOTIFY)
    (
        IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        IN EFI_KEY_DATA *KeyData,
        IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
        OUT VOID **NotifyHandle);
    EFI_STATUS(*UnregisterKeyNotify)
    (
        IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        IN VOID *NotificationHandle);
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

/* SimpleTextInputProtocol */
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
    EFI_STATUS(*Reset)
    (
        IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
        IN BOOLEAN ExtendedVerification);
    EFI_STATUS(*ReadKeyStroke)
    (
        IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
        OUT EFI_INPUT_KEY *Key);
    EFI_EVENT WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

/* SimpleTextOutputProtocol */

typedef struct
{
    INT32 MaxMode;
    INT32 Mode;
    INT32 Attribute;
    INT32 CursorColumn;
    INT32 CursorRow;
    BOOLEAN CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    EFI_STATUS(*Reset)
    (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        IN BOOLEAN ExtendedVerification);
    EFI_STATUS(*OutputString)
    (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        IN CHAR16 *String);
    EFI_STATUS(*TestString)
    (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        IN CHAR16 *String);
    EFI_STATUS(*QueryMode)
    (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL This,
        IN UINTN ModeNumber,
        OUT UINTN *Columns,
        OUT UINTN *Rows);
    EFI_STATUS(*SetMode)
    (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        IN UINTN ModeNumber);
    EFI_STATUS(*SetAttribute)
    (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        IN UINTN Attribute);
    EFI_STATUS(*ClearScreen)
    (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    EFI_STATUS(*SetCursorPosition)
    (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        IN UINTN Column,
        IN UINTN Row);
    EFI_STATUS(*EnableCursor)
    (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
        IN BOOLEAN Visible);
    SIMPLE_TEXT_OUTPUT_MODE *Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

/* @End SimpleTextProtocol */

/* BootServices */

#include "bs.h"

typedef _EFI_BOOT_SERVICES
{
    EFI_TABLE_HEADER Hdr;

    //
    // Task Priority Services
    //
    EFI_RAISE_TPL RaiseTPL;     // EFI 1.0+
    EFI_RESTORE_TPL RestoreTPL; // EFI 1.0+

    //
    // Memory Services
    //
    EFI_ALLOCATE_PAGES AllocatePages; // EFI 1.0+
    EFI_FREE_PAGES FreePages;         // EFI 1.0+
    EFI_GET_MEMORY_MAP GetMemoryMap;  // EFI 1.0+
    EFI_ALLOCATE_POOL AllocatePool;   // EFI 1.0+
    EFI_FREE_POOL FreePool;           // EFI 1.0+

    //
    // Event & Timer Services
    //
    EFI_CREATE_EVENT CreateEvent;    // EFI 1.0+
    EFI_SET_TIMER SetTimer;          // EFI 1.0+
    EFI_WAIT_FOR_EVENT WaitForEvent; // EFI 1.0+
    EFI_SIGNAL_EVENT SignalEvent;    // EFI 1.0+
    EFI_CLOSE_EVENT CloseEvent;      // EFI 1.0+
    EFI_CHECK_EVENT CheckEvent;      // EFI 1.0+

    //
    // Protocol Handler Services
    //
    EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;     // EFI 1.0+
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface; // EFI 1.0+
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface; // EFI 1.0+
    EFI_HANDLE_PROTOCOL HandleProtocol;                          // EFI 1.0+
    VOID *Reserved;                                              // EFI 1.0+
    EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;         // EFI  1.0+
    EFI_LOCATE_HANDLE LocateHandle;                              // EFI 1.0+
    EFI_LOCATE_DEVICE_PATH LocateDevicePath;                     // EFI 1.0+
    EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;   // EFI 1.0+

    //
    // Image Services
    //
    EFI_IMAGE_UNLOAD LoadImage;              // EFI 1.0+
    EFI_IMAGE_START StartImage;              // EFI 1.0+
    EFI_EXIT Exit;                           // EFI 1.0+
    EFI_IMAGE_UNLOAD UnloadImage;            // EFI 1.0+
    EFI_EXIT_BOOT_SERVICES ExitBootServices; // EFI 1.0+

    //
    // Miscellaneous Services
    //
    EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount; // EFI 1.0+
    EFI_STALL Stall;                                    // EFI 1.0+
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;            // EFI 1.0+

    //
    // DriverSupport Services
    //
    EFI_CONNECT_CONTROLLER ConnectController;       // EFI 1.1
    EFI_DISCONNECT_CONTROLLER DisconnectController; // EFI 1.1+

    //
    // Open and Close Protocol Services
    //
    EFI_OPEN_PROTOCOL OpenProtocol;                        // EFI 1.1+
    EFI_CLOSE_PROTOCOL CloseProtocol;                      // EFI 1.1+
    EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation; // EFI 1.1+

    //
    // Library Services
    //
    EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;                                    // EFI 1.1+
    EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;                                    // EFI 1.1+
    EFI_LOCATE_PROTOCOL LocateProtocol;                                             // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;   // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces; // EFI 1.1+*

    //
    // 32-bit CRC Services
    //
    EFI_CALCULATE_CRC32 CalculateCrc32; // EFI 1.1+

    //
    // Miscellaneous Services
    //
    EFI_COPY_MEM CopyMem;              // EFI 1.1+
    EFI_SET_MEM SetMem;                // EFI 1.1+
    EFI_CREATE_EVENT_EX CreateEventEx; // UEFI 2.0+
}
EFI_BOOT_SERVICES;

/* @End BootServices */

/* RuntimeServices */
typedef struct _EFI_RUNTIME_SERVICES
{
    EFI_TABLE_HEADER Hdr;
    CHAR8 _buf_rs1[24];
    UINT64 _buf_rs2[4];
    UINT64 _buf_rs3[2];
    UIIINT64 _buf_rs4[3];
    UINT64 _buf_rs5;
    VOID(*ResetSystem)
    (
        IN EFI_RESET_TYPE ResetType,
        IN EFI_STATUS ResetStatus,
        IN UINTN DataSize,
        IN VOID *ResetData OPTIONAL);
} EFI_RUNTIME_SERVICES;

/* @End RuntimeServices */

/* SystemTable */

typedef struct
{
    EFI_TABLE_HEADER Hdr;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigurationTable;
} EFI_SYSTEM_TABLE;

/* @End SystemTable */

/* GraphicsOutputProtocol */

typedef enum _EFI_GRAPHIICS_PIXEL_FORMAT
{
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct
{
    UINT32 RedMask;
    UINT32 GreenMask;
    UINT32 BlueMask;
    UINT32 ReservedMask;
} EFI_PIXEL_BITMASK;

typedef struct
{
    UINT32 Version;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    EFI_PIXEL_BITMASK PixelInformation;
    UINT32 PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct
{
    UINT32 MaxMode;
    UINT32 Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    UINTN SizeOfInfo;
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    UINTN FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct
{
    UINT8 Blue;
    UINT8 Green;
    UINT8 Red;
    UINT8 Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef enum
{
    EfiBltVideoFill,
    EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo,
    EfiBltVideoToVideo,
    EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef struct EFI_GRAPHICS_OUTPUT_PROTCOL
{
    EFI_STATUS(*QueryMode)
    (
        IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
        IN UINT32 ModeNumber,
        OUT UINTN *SizeOfInfo
            OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);
    EFI_STATUS(*SetMode)
    (
        IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
        IN UINT32 ModeNumber);
    EFI_STATUS(*Blt)
    (
        IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
        IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, OPTIONAL IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,
        IN UINTN SourceX,
        IN UINTN SourceY,
        IN UINTN DestinationX,
        IN UINTN DestinationY,
        IN UINTN Width,
        IN UINTN Height,
        IN UINTN Delta OPTIONAL);
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

/* @End GraphicsOutputProtocol */

/* SimplePointerProtocol */

typedef struct
{
    INT32 RelativeMovementX;
    INT32 RelativeMovementY;
    INT32 RelativeMovementZ;
    BOOLEAN LeftButton;
    BOOLEAN RightButton;
} EFI_SIMPLE_POINTER_STATE;

typedef struct
{
    UINT64 ResolutionX;
    UINT64 ResolutionY;
    UINT64 ResolutionZ;
    BOOLEAN LeftButton;
    BOOLEAN RightButton;
} EFI_SIMPLE_POINTER_MODE;

typedef struct _EFI_SIMPLE_POINTTER_PROTOCOL
{
    EFI_STATUS(*Reset)
    (
        IN EFI_SIMPLE_POINTER_PROTOCOL *This,
        IN BOOLEAN ExtendedVerification);
    EFI_STATUS(*GetState)
    (
        IN EFI_SIMPLE_POINTER_PROTOCOL *This,
        OUT EFI_SIMPLE_POINTER_STATE *State);
    EFI_EVENT WaitForInput;
    EFI_SIMPLE_POINTER_MODE *Mode;
};

/* @End SimplePointerProtocol */

#endif