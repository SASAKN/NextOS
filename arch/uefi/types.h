#ifndef _UEFI_TYPES_H
#define _UEFI_TYPES_H

#include <neox/types.h>
#include "../arch.h"

/* Boolean */
typedef unsigned char Boolean;

/* INTN */
typedef signed long INTN;

/* UINTN */
typedef unsigned long UINTN;

/* INT8 */
typedef signed char INT8;

/* UINT8 */
typedef unsigned char UINT8;

/* INT16 */
typedef short INT16;

/* UINT16 */
typedef unsigned short UINT16;

/* INT32 */
typedef int INT32;

/* UINT32 */
typedef unsigned int UINT32;

/* INT64 */
typedef long INT64;

/* UINT64 */
typedef unsigned long UINT64;

/* CHAR8 */
typedef char CHAR8;

/* CHAR16 */
typedef unsigned short CHAR16;

/* VOID */
typedef void VOID;

/* EFI_GUID */
typedef struct {
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
} EFI_GUID; 

/* EFI_STATUS */
typedef UINTN EFI_STATUS;

/* EFI_HANDLE */
typedef VOID *EFI_HANDLE;

/* EFI_EVENT */
typedef VOID *EFI_EVENT;

/* EFI_LBA */
typedef UINT64 EFI_LBA;

/* EFI_TPL */
typedef UINTN EFI_TPL;

/* EFI_TIME */
typedef struct {
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





#endif
