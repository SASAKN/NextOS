#ifndef _NEOX_PANIC_H
#define _NEOX_PANIC_H

/* deliberate panic */
int panic( void ){
    int panic;
    panic = 1;
    return 1; /* Returns 1 if it's an intentional panic. */
};

#endif