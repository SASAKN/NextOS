#ifndef _EFI_IO_H
#define _EFI_IO_H

// Prototype
void PrintOK(void);
void PrintWarn(void);
void PrintError(void);
EFI_STATUS open_root_dir(EFI_HANDLE IM, EFI_FILE_PROTOCOL **root);
UINT64 open_file_read(EFI_FILE_PROTOCOL *root, CHAR16 *file_path, EFI_FILE_PROTOCOL *file);


#endif // _EFI_IO_H