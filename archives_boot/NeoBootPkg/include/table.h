#ifndef _BOOT_TABLE_H
#define _BOOT_TABLE_H

typedef struct neoboot_table
{
    struct mem_map
    {
        uint64_t buffer_size;
        void *buffer;
        uint64_t map_size;
        uint64_t map_key;
        uint64_t descriptor_size;
        uint32_t descriptor_version;
        uint64_t memmap_desc_entry;
    } memory_map; //メモリーマップ
} neoboot_table_t;

#endif