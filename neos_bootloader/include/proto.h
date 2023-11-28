#ifndef _NEOBOOT_PROTO_H
#define _NEOBOOT_PROTO_H

//Print
void PrintError(void); 
void PrintWarn(void); 
void PrintGoodBye(void);
void PrintOK(void);  

//MemoryMap
void *malloc(size_t size);
void free(void* ptr);
void init_memmap(struct MemoryMap *map, void* buffer);
const CHAR16 *get_memtype(EFI_MEMORY_TYPE type);
EFI_STATUS get_memmap(struct MemoryMap *map);
EFI_STATUS print_memmap(struct MemoryMap *map);
EFI_STATUS save_memmap(struct MemoryMap *map, DIR *root);

// File
FILE **create_file(DIR *root, CHAR16 file_path);

#endif