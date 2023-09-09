#ifndef _UEFI_TYPES_H
#define _UEFI_TYPES_H

#include <neox/types.h>
#include "../arch.h"

/* IN OUT */
#ifndef IN
#define IN
#define OUT
#define OPTIONAL
#endif

/* EFIAPI */
#ifndef EFIAPI
#define EFIAPI
#endif

/* Boolean */
typedef unsigned char BOOLEAN;

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


/* EFI_RESET_TYPE */
typedef enum
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

/* EFI_DEVICE_PATH_PROTOCOL */
typedef struct
{
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

/* EFI_TABLE_HEADER */
typedef struct
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

/* EFI_STATUS */
typedef unsigned long long EFI_STATUS;

/* EFI_HANDLE */
typedef VOID *EFI_HANDLE;

/* EFI_EVENT */
typedef VOID *EFI_EVENT;

/* EFI_LBA */
typedef UINT64 EFI_LBA;

/* EFI_TPL */
typedef UINTN EFI_TPL;

#endif
