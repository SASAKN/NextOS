#ifndef _CONFIG_H
#define _CONFIG_H

/* OS release and version numbers  */
#define OS_NAME "neos"     /* OS Name */
#define OS_CODENAME "none" /* OS Codename */
#define OS_BOOTLOADER "" /* Currently only NeoBoot is supported */
#define OS_RELEASE "1"     /* OS Version */
#define OS_VERSION "1.0.0" /* OS Release */
#define OS_DEVELOPER "SASAKEN" /* OS Developer */
#define OS_EDITION "DEV" /* OS Editions (DEV, NONE, RELEASE) */
#define OS_PLATFORM "ALL" /*OS PLATFORMS (UEFI_X64, ALL) */


/* Machine Definitions */
#include <neos/machine.h>

#endif /* _CONFIG_H */