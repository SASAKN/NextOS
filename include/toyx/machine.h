/* Machine Definitions */
#ifndef


#ifndef _TOYX_MACHINE_H
#define _TOYX_MACHINE_H

#define MACHINE     _TOYX_MACHINE


/* CPU Architectures */

/* Non-X64_PC definitions are not currently used */

/* CPU Definitions */
#define X64_PC      _MACHINE_X64    
#define X86_PC      _MACHINE_X86 
#define RISCV_PC    _MACHINE_RISCV 
#define ARM_PC      _MACHINE_ARM    

/* Non-EFI_PC definitions are not currently used */

/* Definitions to use for boot systems */
#define EFI_PC      _EFI_PC     /* Supported UEFI Computer */
#define BIOS_PC     _BIOS_PC    /* Supported BIOS Computer */



#endif /* _TOYX_MACHINE_H */