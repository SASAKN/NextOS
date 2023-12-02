#ifndef _EFI_IO_H
#define _EFI_IO_H

// Prototype
void PrintOK(void);
void PrintWarn(void);
void PrintError(void);
EFI_STATUS open_root_dir(EFI_HANDLE IM, EFI_FILE_PROTOCOL **root);
EFI_STATUS open_file_read(UINTN *file_size, EFI_FILE_PROTOCOL *root, EFI_FILE_PROTOCOL *file, CHAR16 *file_path);

#endif // _EFI_IO_H