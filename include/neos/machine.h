/* Machine Definitions */
#ifndef _NEOS_MACHINE_H
#define _NEOS_MACHINE_H

/* Default NEOS CPU */
#define _NEOS_MACHINE   _MACHINE_X64

/*Default NEOS Boot Systems*/
#define _NEOS_BOOT_SYSTEM   _EFI_PC

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
#if (_NEOS_MACHINE == _MACHINE_X64)
#define _NEOS_CHIP      _CHIP_INTEL
#endif

/* Errors */
#ifndef _NEOS_MACHINE
error "In <include/neos/machine.h> please define _NEOS_MACHINE"
#endif

#ifndef _NEOS_CHIP
error "In <include/neos/machine.h> please define _NEOS_CHIP"
#endif

#if (_NEOS_MACHINE == 0)
error "_NEOS_MACHINE has incorrect value (0)"
#endif

#define MACHINE     _NEOS_MACHINE


/* CPU Architectures */

/* Non-X64_PC definitions are not currently used */

/* CPU Definitions */
#define X64_PC      _MACHINE_X64    
#define X86_PC      _MACHINE_X86

/* Non-EFI_PC definitions are not currently used */

/* Definitions to use for boot systems */
#define EFI_PC      _EFI_PC     /* Supported UEFI Computer */
#define BIOS_PC     _BIOS_PC    /* Supported BIOS Computer */

#endif /* _NEOS_MACHINE_H */