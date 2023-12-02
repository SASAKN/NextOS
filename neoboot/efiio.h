#ifndef _EFI_IO_H
#define _EFI_IO_H

// Prototype
void PrintOK(void);
void PrintWarn(void);
void PrintError(void);
EFI_STATUS open_root_dir(EFI_HANDLE IM, EFI_FILE_PROTOCOL **root);

#endif // _EFI_IO_H