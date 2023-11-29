#ifndef _NEOBOOT_FILE_H
#define _NEOBOOT_FILE_H

// ProtoType
EFI_STATUS open_root_dir(EFI_HANDLE IM, EFI_FILE_PROTOCOL **root);
EFI_FILE_PROTOCOL *create_file(EFI_FILE_PROTOCOL *root, CHAR16 *file_path);

#endif //_NEOBOOT_FILE_H