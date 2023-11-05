#ifndef _BOOT_TABLE_H
#define _BOOT_TABLE_H

#include "types.h"
#include "efi.h"
#include "graphics.h"
#include "mem.h"

typedef struct os_info {
    /* OSの情報 */
    char *os_name;
    char *os_author;
    char *os_license;
} neos_os_info_t;

/* NeosBootTable */
typedef struct NEOS_BOOT_TABLE {
    struct MemoryMap mem_map;
    
} neos_boot_table_t;


#endif