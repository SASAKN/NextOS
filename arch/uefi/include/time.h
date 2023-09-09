#ifndef _ARCH_UEFI_TIME_H
#define _ARCH_UEFI_TIME_H

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