/* UEFI Config File */
#ifndef _EFI_CONFIG_H
#define _EFI_CONFIG_H

#include "types.h" /* Must be First */

/* Defines */

/* File Name */
#define KERNEL_FILE L"neos.elf"
#define CONFIG_FILE L"config.boot"

/* Directory Name */
#define OS_APPS     L"apps/"
#define OS_SERVER   L"servers/"
#define OS_DRIVER   L"drivers/"
#define OS_FUNCTION L"functions/"

/* Boot Setting */
#define BOOT_DEVELOPER_MODE 1 /* Debug Mode */
#define SPLASH              1 /* Boot Splash */  

#endif