#include "../include/efi.h"

/* ブートの範囲内で共通の関数 */
void putc(UINT16 c) {
    UINT16 str[2] = L" ";
    str[0] = c;
    ST->ConOut->OutputString(ST->ConOut, str);
};

void puts(UINT16 *s) {
    ST->ConOut->OutputString(ST->ConOut, s);
};

UINT64 strlen (UINT16 *str) {
    UINT64 length = 0;
    /* ヌル文字になるまで、Lengthを増やしていく */
    while (*str++ != L'\0')
        length++;
    return length;
};

