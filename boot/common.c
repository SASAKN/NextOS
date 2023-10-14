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

/* エラーチェック */
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

/* assert関数は、エラーを表示する */
void assert (UINT64 status, UINT16 *mess) {
    if (status == 0x8000000000000005) {
        puts(L"Error: EFI_BUFFER_TOO_SMALL");
        puts(L"\r\n");
    }
    if (!check_warn_error(status, mess))
        while(1);
};
/* CHARデータ型のものをintに変換する関数  */
int custom_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // ホワイトスペースをスキップ
    while (str[i] == ' ' || str[i] == '\t') {
        i++;
    }

    // 符号を処理
    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i] == '-') ? -1 : 1;
        i++;
    }

    // 数値を解析して整数に変換
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

void zero_pad(char *str, int width) {
    int str_length = custom_strlen(str);

    if (str_length < width) {
        int pad_count = width - str_length;

        // 移動元と移動先の位置を計算
        char *src = str + str_length;  // 末尾から進む
        char *dest = str + width;      // 末尾から進む

        // 文字列を右にずらす
        while (src >= str) {
            *(--dest) = *(--src);
        }

        // 残りの部分を '0' で埋める
        while (pad_count > 0) {
            *(str++) = '0';
            pad_count--;
        }

        // 文字列の終了を示すヌル文字を追加
        *str = '\0';
    }
}

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

/* 1文字のワイド文字を、マルチバイト文字に変換 */
void custom_wctomb(wchar_t wc, char* dest, size_t destSize) {
    if (destSize < 2) {
        return; // バッファが小さすぎる場合、何もしない
    }
    dest[0] = (char)wc;
    dest[1] = '\0'; // NULL終端文字を追加
};

/* Printf 標準ライブラリなどにあるやつ */
void custom_printf(const char *format, ...) {
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
                    /* 1文字出力 */
                    int c = va_arg(args, int);
                    putc(c);
                    break;
                }
                case 's': {
                    /* 文字列の出力 */
                    const char *str = va_arg(args, const char *);
                    while (*str) {
                        putc(*str);
                        str++;
                    }
                    break;
                }
                case 'd': {
                    /* 整数を10進数で表示 */
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

/* Wprintf 標準ライブラリなどにあるやつ */
void custom_wprintf(const wchar_t *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format != L'%') {
            putc(*format);
        } else {
            format++;
            if (*format == L'\0') {
                break; // 不完全なフォーマット文字列を処理
            }

            switch (*format) {
                case L'c': {
                    /* 1文字出力 */
                    int c = va_arg(args, int);
                    putc(c);
                    break;
                }
                case L's': {
                    /* 文字列の出力 */
                    wchar_t *wsz = va_arg(args, wchar_t *);
                    char str[2]; // 1文字 + NULL終端文字
                    char fullStr[200];
                    int fullStrIndex = 0;
                    for (int i = 0; wsz[i] != L'\0'; i++) {
                        custom_wctomb(wsz[i], str, sizeof(str));
                        fullStr[fullStrIndex] = str[0];
                        fullStrIndex++;
                    };
                    fullStr[fullStrIndex] = '\0';
                    char *buffer = fullStr;
                    while(*buffer) {
                        putc(*buffer);
                        buffer++;
                    }
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
                    /* 10進数のテキスト生成 */
                    unsigned int val = va_arg(args, unsigned int);
                    dest += itoa(dest, end - dest, val, 10);
                    break;
                }
                case 'x': {
                    /* 16進数のテキスト生成 */
                    unsigned int val = va_arg(args, unsigned int);
                    dest += itoa(dest, end - dest, val, 16);
                    break;
                }
                case 's': {
                    /* Charデータ型のテキスト生成 */
                    const char *arg_str = va_arg(args, const char *);
                    while (*arg_str && dest < end) {
                        *dest = *arg_str;
                        dest++;
                        arg_str++;
                    }
                    break;
                }
                case '-': {
                    format++;
                    if (*format == 'l') {
                        format++;
                        if (*format == 's') {
                            /* これなら成功次のステップへ */
                            wchar_t *wsz = va_arg(args, wchar_t *);
                            char str[2]; // 1文字 + NULL終端文字
                            char fullStr[200];
                            int fullStrIndex = 0;
                            for (int i = 0; wsz[i] != L'\0'; i++) {
                                custom_wctomb(wsz[i], str, sizeof(str));
                                fullStr[fullStrIndex] = str[0];
                                fullStrIndex++;
                            };
                            fullStr[fullStrIndex] = '\0';
                            char *buffer = fullStr;
                            while (*buffer && dest < end) {
                                *dest = *buffer;
                                dest++;
                                buffer++;
                            };
                            format++;
                        } else {
                            puts(L"[ Text_gen ]: Format error!");
                        }
                    } else {
                        puts(L"[ Text_gen ]: Format error!");
                    }
                }
                case '0': {
                    format++;
                    format++; /* xが予想される場所まで移動 */
                    if (*format == 'l') {
                        format++;
                        if (*format == 'x') {
                            /* 16進数のテキスト生成 */
                            format--;
                            format--;
                            unsigned int val = va_arg(args, unsigned int);
                            int tmp = custom_atoi(format);
                            dest += itoa(dest, end - dest, val, 16);
                            zero_pad(dest, tmp);
                        }
                    } else {
                        puts(L"[ Text_gen ]: Format error!");
                    }
                    format++;
                    format++;
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