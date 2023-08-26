#ifndef _NEOX_SYSCALL_H
#define _NEOX_SYSCALL_H

/* Kernel SystemCall */ 
#define _NEOX_CALL  500 /* Calls above this value will block. */

#include <neox/panic.h>

#if (_NEOX_CALL > 500) /* Kernel Panic */
#endif

#endif /* _NEOX_SYSCALL_H */