#ifndef _BOOT_BASIC_H
#define _BOOT_BASIC_H


size_t strlen(const char *str) {
    const char *s = str;
    while (*s) {
        s++;
    }
    return s - str;
}

#endif