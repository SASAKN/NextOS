/*===========================================================================*
 *		sys_config.h		     *
 *===========================================================================*/
#ifndef _TOYX_SYS_CONFIG_H
#define _TOYX_SYS_CONFIG_H 1

/* Default Toyx CPU */
#define _TOYX_MACHINE   _MACHINE_X64

/*Default Toyx Boot Systems*/
#define _TOYX_BOOT_SYSTEM   _EFI_PC

/* Non-X64_PC definitions are not currently used */

/* CPU Architectures */
#define _MACHINE_X64    1
#define _MACHINE_X86    2

/* Non-EFI_PC definitions are not currently used */

/* Boot Systems */
#define _EFI_PC         1
#define _BIOS_PC        2

/* CPU Chips */
#define _CHIP_INTEL 1

/* CPU Chip */
#if (_TOYX_MACHINE == _MACHINE_X64)
#define _TOYX_CHIP      _CHIP_INTEL
#endif

/* Errors */
#ifndef _TOYX_MACHINE
error "In <toyx/machine.h> please define _TOYX_MACHINE"
#endif

#ifndef _TOYX_CHIP
error "In <toyx/machine.h> please define _TOYX_CHIP"
#endif

#if (_TOYX_MACHINE == 0)
error "_TOYX_MACHINE has incorrect value (0)"
#endif

#endif

/*===========================================================================*
 *		machine.h	     *
 *===========================================================================*/
/* Machine Definitions */
#ifndef _TOYX_MACHINE_H
#define _TOYX_MACHINE_H

#define MACHINE     _TOYX_MACHINE


/* CPU Architectures */

/* Non-X64_PC definitions are not currently used */

/* CPU Definitions */
#define X64_PC      _MACHINE_X64    
#define X86_PC      _MACHINE_X86

/* Non-EFI_PC definitions are not currently used */

/* Definitions to use for boot systems */
#define EFI_PC      _EFI_PC     /* Supported UEFI Computer */
#define BIOS_PC     _BIOS_PC    /* Supported BIOS Computer */



#endif /* _TOYX_MACHINE_H */