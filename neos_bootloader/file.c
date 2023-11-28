#include "include/proto.h"
#include "include/elf.h"
#include "include/file.h"
#include <Uefi.h>

// SimpleFileSystemプロトコルを開く
EFI_STATUS open_sfsp(void) {

}

//ファイルを作る
FILE **create_file(DIR *root, CHAR16 file_path) {
    FILE **file;
    status = root->Open(root, file, file_path, EFI_FILE_MODE_READ | EFI_FILE_MODE_CREATE | EFI_FILE_MODE_WRITE);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Create File : %r\n", status);
    }
    return file;
}