#include "efi.h"

EFI_SYSTEM_TABLE *gST;
EFI_BOOT_SERVICES *gBS;
EFI_RUNTIME_SERVICES *gRT;

EfiApplicationEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)

{
    EFI_STATUS Status;
    EFI_TIME *Time;

    gST = SystemTable;
    gBS = gST->BootServices;
    gRT = gST->RuntimeServices;

    //
    // Use EFI System Table to print "Hello World" to the active console output
    // device.
    //
    Status = gST->ConOut->OutputString(gST->ConOut, L"Hello world\n\r");
    if (EFI_ERROR(Status))
    {
        return Status;
    }

    //
    // Use EFI Boot Services Table to allocate a buffer to store the current time
    // and date.
    //
    Status = gBS->AllocatePool(
        EfiBootServicesData,
        sizeof(EFI_TIME),
        (VOID \**)&Time);
    if (EFI_ERROR(Status))
    {
        return Status;
    }

    //
    // Use the EFI Runtime Services Table to get the current time and date.
    //
    Status = gRT->GetTime(Time, NULL) if (EFI_ERROR(Status))
    {
        return Status;
    }

    return Status;
}