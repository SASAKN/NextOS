#include "include/efi.h"
#include "include/proto.h"

/* １文字だけ出力できる関数 */
void putc(UINT16 c) {
    UINT16 str[2] = L" ";
    str[0] = c;
    ST->ConOut->OutputString(ST->ConOut, str);
};

/* Printfみたいな色々な文字列を、送ったら、出力する関数 */
void puts(UINT16 *s) {
    ST->ConOut->OutputString(ST->ConOut, s);
};

/* EDK2などに合わせるためにあるだけ */
void Print(UINT16 *s) {
    ST->ConOut->OutputString(ST->ConOut, s);
};

/* １文字ずつ取得 */
UINT16 getc(void) {
    EFI_INPUT_KEY key;
    UINT64 waitidx;

    ST->BootServices->WaitForEvent(1, &(ST->ConIn->WaitForKey),
                        &waitidx);
    while (ST->ConIn->ReadKeyStroke(ST->ConIn, &key));
    
    return key.UnicodeChar;
};

/* いっぱい入力できる関数 */
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

/* 16進数の出力 */
void PrintHex(UINT64 val, UINT8 num_degits) {
    UINT16 u_val;
    UINT16 str[100];

    for (int i = num_degits - 1; i >= 0; i--) {
        u_val = (UINT16)(val & 0x0f);
        if (u_val < 0xa)
            str[i] = L'0' + u_val;
        else
            str[i] = L'A' + (u_val - 0xa);
        val >>= 4;
    };
    str[num_degits] = L'\0';

    puts(str);
};

UINT8 check_warn_error (UINT64 status, UINT16 *mess) {
    if(status) {
        puts(mess);
        puts(L":");
        PrintHex(status, 16);
        puts(L"\r\n");
    };

    return !status;
}

void assert (UINT64 status, UINT16 *mess) {
    if (!check_warn_error(status, mess))
        while(1);
};