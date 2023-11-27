#include "include/proto.h"
#include "include/memory_map.h"
#include "/Users/kenta/edk2/MdePkg/Include/Uefi.h"

// Allocate Pool
void *malloc(size_t size) {
    void *src;
    EFI_STATUS status;
    src = NULL;
    status = gBS->AllocatePool(EfiLoaderData, size, &src);
    if (EFI_ERROR(status)) {
        PrintError();
    }
}