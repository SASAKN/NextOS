#include "include/efi.h"
#include "include/proto.h"

/* ブートの範囲内で共通の関数 */
void putc(UINT16 c) {
    UINT16 str[2] = L" ";
    str[0] = c;
    ST->ConOut->OutputString(ST->ConOut, str);
};

void puts(UINT16 *s) {
    ST->ConOut->OutputString(ST->ConOut, s);
};

UINT16 getc(void) {
    EFI_INPUT_KEY key;
    UINT64 waitidx;

    ST->BootServices->WaitForEvent(1, &(ST->ConIn->WaitForKey),
                        &waitidx);
    while (ST->ConIn->ReadKeyStroke(ST->ConIn, &key));
    
    return key.UnicodeChar;
};

UINT32 gets(UINT16 *buf, UINT32 buf_size) {
    UINT32 i;

    for(i = 0; i < buf_size - 1;) {
        buf[i] = getc();
        putc(buf[i]);
        if (buf[i] == L'\r') {
            putc(L'\n');
            break;
        };
        i++;
    };
    buf[i] = L'\0';

    return i;
};



UINT64 strlen (UINT16 *str) {
    UINT64 length = 0;
    /* ヌル文字になるまで、Lengthを増やしていく */
    while (*str++ != L'\0')
        length++;
    return length;
};

