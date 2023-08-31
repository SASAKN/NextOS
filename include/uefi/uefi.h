#ifndef _UEFI_H
#define _UEFI_H

//Always First
#include <neox/types.h>

//Don't Need Defines
#define EFI_BLACK	0x00
#define EFI_BLUE	0x01
#define EFI_GREEN	0x02
#define EFI_CYAN	0x03
#define EFI_RED	0x04
#define EFI_MAGENTA	0x05
#define EFI_BROWN	0x06
#define EFI_LIGHTGRAY	0x07
#define EFI_BRIGHT	0x08
#define EFI_DARKGRAY	0x08
#define EFI_LIGHTBLUE	0x09
#define EFI_LIGHTGREEN	0x0A
#define EFI_LIGHTCYAN	0x0B
#define EFI_LIGHTRED	0x0C
#define EFI_LIGHTMAGENTA	0x0D
#define EFI_YELLOW	0x0E
#define EFI_WHITE	0x0F

#define EFI_BACKGROUND_BLACK	0x00
#define EFI_BACKGROUND_BLUE	0x10
#define EFI_BACKGROUND_GREEN	0x20
#define EFI_BACKGROUND_CYAN	0x30
#define EFI_BACKGROUND_RED	0x40
#define EFI_BACKGROUND_MAGENTA	0x50
#define EFI_BACKGROUND_BROWN	0x60
#define EFI_BACKGROUND_LIGHTGRAY	0x70

#define MEDIA_DEVICE_PATH	0x04
#define MEDIA_FILEPATH_DP	0x04

#define END_DEVICE_PATH_TYPE	0x7f
#define END_ENTIRE_DEVICE_PATH_SUBTYPE	0xff

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL	0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL		0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL		0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER	0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER		0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE		0x00000020

#define EFI_SUCCESS	0

#define EVT_TIMER	0x80000000
#define EVT_RUNTIME	0x40000000
#define EVT_NOTIFY_WAIT	0x00000100
#define EVT_NOTIFY_SIGNAL	0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES	0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE	0x60000202

#define TPL_APPLICATION	4
#define TPL_CALLBACK	8
#define TPL_NOTIFY	16
#define TPL_HIGH_LEVEL	31

#define EFI_SC_ESC	0x0017

typedef struct {
    kFalse = 0,
    kTrue = 1
} Boolean;

// Need Defines

typedef struct{
    unsigned short ScanCode;
    unsigned short UnicodeChar;
} EFI_INPUT_KEY;

typedef struct{
    unsigned int Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} EFI_GUID;

 typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaim
} EFI_MEMORY_TYPE;

typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef enum {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef enum {
    TimerCancel,
    TimerPeriodic,
    TimerRelactive
} EFI_TIMER_DELAY;

typedef struct {
    unsigned char Type;
    unsigned char SubType;
    unsigned char Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct {
    char _buf1[44];
    struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL{
        unsigned long long _buf;
        unsigned long long (*ReadKeyStroke)(
            struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
            struct EFI_INPUT_KEY *key);
        void *WaitForKey;  
    } *ConIn;
    unsigned long long _buf2;
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
        unsigned long long _buf;
        unsigned long long (*OutpuutString)(
            struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            unsigned long long *String);
    }

} EFI_SYSTEM_TABLE;



#endif