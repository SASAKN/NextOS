/* UEFI Config File */
#ifndef _EFI_CONFIG_H
#define _EFI_CONFIG_H

#include "types.h" /* Must be First */

/* Defines */

/* File Name */
#define KERNEL_FILE L"\\kernel.elf"
#define CONFIG_FILE L"config.boot"

/* Directory Name */
#define OS_APPS     L"apps/"
#define OS_SERVER   L"servers/"
#define OS_DRIVER   L"drivers/"
#define OS_FUNCTION L"functions/"

/* Minixエミュレーション */
#define _MINIX_ROOT L"minix/"

/* Boot Setting */
#define BOOT_DEVELOPER_MODE 1 /* Debug Mode */
#define SPLASH              1 /* Boot Splash */  

/* Boot Config */
struct boot_config {
    UINT64 kernel;
    UINT64 servers;
    UINT64 functions;
    UINT64 drivers;
    UINT64 apps; 
};
/* メモリの割り当て設定を行うことができる構造体です。 */

#endif