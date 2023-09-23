#ifndef _BOOT_TYPES_H
#define _BOOT_TYPES_H

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


#endif