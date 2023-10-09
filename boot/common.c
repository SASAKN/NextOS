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
};

/* StrLen 文字数を数える */
UINTN EFIAPI strlen(const CHAR8 *str) {
    UINTN len;
    for (len = 0; *str != L'\0'; str++) {
        len++;
    }
    return len;
};

void assert (UINT64 status, UINT16 *mess) {
    if (status == 0x8000000000000005) {
        puts(L"Error: EFI_BUFFER_TOO_SMALL");
        puts(L"\r\n");
    }
    if (!check_warn_error(status, mess))
        while(1);
};

/* Printf 標準ライブラリなどにあるやつ */
void printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format != '%') {
            putc(*format);
        } else {
            format++;
            if (*format == '\0') {
                break; // 不完全なフォーマット文字列を処理
            }

            switch (*format) {
                case 'c': {
                    int c = va_arg(args, int);
                    putc(c);
                    break;
                }
                case 's': {
                    const char *str = va_arg(args, const char *);
                    while (*str) {
                        putc(*str);
                        str++;
                    }
                    break;
                }
                case 'd': {
                    /* ここには、何も実装がありません */
                    // int num = va_arg(args, int);
                    // // カスタム整数から文字列への変換ロジックを呼び出す
                    // // この例では未実装
                    // // custom_itoa_base(buffer, sizeof(buffer), num, 10);
                    // // custom_puts(buffer);
                    break;
                }
                default: {
                    putc('%');
                    putc(*format);
                }
            }
        }
        format++;
    }

    va_end(args);
};

/* 標準ライブラリで実装されているitoa */
size_t itoa(char *str, size_t max_size, unsigned int value, int base) {
    if (base < 2 || base > 36 || max_size < 2) {
        return 0; // エラー: サポートされていない基数や不十分なバッファサイズ
    }

    size_t i = 0;
    str[i++] = '\0';

    while (value > 0 && i < max_size) {
        int digit = value % base;
        str[i++] = (digit < 10) ? (char)('0' + digit) : (char)('a' + digit - 10);
        value /= base;
    }

    if (i < max_size) {
        str[i] = '\0'; // 文字列を逆順にして null 終端
        for (size_t j = 0; j < i / 2; j++) {
            char temp = str[j];
            str[j] = str[i - j - 1];
            str[i - j - 1] = temp;
        }
    } else {
        return 0; // エラー: バッファオーバーフロー
    }

    return i - 1; // null 終端文字を除いた文字列の長さ
};

/* sprintf的なやつ */
void text_gen(char *str, size_t max_size, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char *dest = str;
    char *end = str + max_size - 1; // Leave space for null-terminator

    while (*format && dest < end) {
        if (*format != '%') {
            *dest = *format;
            dest++;
        } else {
            format++;
            if (*format == '\0') {
                break; // Handle incomplete format string
            }

            switch (*format) {
                case 'u': {
                    unsigned int val = va_arg(args, unsigned int);
                    dest += itoa(dest, end - dest, val, 10);
                    break;
                }
                case 'x': {
                    unsigned int val = va_arg(args, unsigned int);
                    dest += itoa(dest, end - dest, val, 16);
                    break;
                }
                case 's': {
                    const char *arg_str = va_arg(args, const char *);
                    while (*arg_str && dest < end) {
                        *dest = *arg_str;
                        dest++;
                        arg_str++;
                    }
                    break;
                }
                default: {
                    // Handle unknown format specifier
                    *dest = *format;
                    dest++;
                }
            }
        }
        format++;
    }

    *dest = '\0'; // Null-terminate the string
    va_end(args);
};

