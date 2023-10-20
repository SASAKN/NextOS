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

/* 16進数のジェネレート */
void hex_gen(UINT16* out, UINT64 val, UINT8 num_degits) {
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
    for (int i = 0; i < num_degits+ 1; i++) {
        out[i] = str[i];
    };
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

void custom_strcat(char *dest, const char *src) {
    // デスティネーションの終端まで移動
    while (*dest) {
        dest++;
    }

    // ソース文字列をデスティネーションにコピー
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0'; // 文字列の終端を追加
}

/* Strcpy - 標準ライブラリーにあるやつ */
void custom_strcpy(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // 文字列の終端を追加
}

void* custom_memset(void *dst, int c, size_t n) {
    size_t i;
    UINT8 *str;
    i = 0;
    str = (UINT8 *)dst;
    while (i < n) {
        str[i] = (UINT8)c;
        i++;
    };
    return (dst);
}

void custom_memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    if (d < s) {
        // ソースと宛先のメモリブロックが重なっていない場合、前から後ろにコピー
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else if (d > s) {
        // ソースと宛先のメモリブロックが重なっている場合、後ろから前にコピー
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }
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
                    /* 10進数を16進数に変換したテキスト生成 */
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
                        };
                    };
                }
                case '0': {
                    format++; /* ゼロ埋めの数字が予想される */
                    int length = 0;/* ゼロ埋めあとの、文字桁数 */
                    /* 文字桁数で条件分岐 */
                    if (*format == '1') {
                        format++;
                        if (*format == '6') {
                            length = 16;
                            format++;
                            format++;
                            break;
                        };
                        length = 1;
                    } else if (*format == '2') {
                        format++;
                        length = 2;
                    } else if (*format == '3') {
                        format++;
                        length = 3;
                    } else if (*format == '4') {
                        format++;
                        length = 4;
                    } else if (*format == '5') {
                        format++;
                        length = 5;
                    } else if (*format == '6') {
                        format++;
                        length = 6;
                    } else if (*format == '7') {
                        format++;
                        length = 7;
                    } else if (*format == '8') {
                        format++;
                        length = 8;
                    } else if (*format == '9') {
                        format++;
                        length = 9;
                    } else if (*format == '1') {
                    }
                    if (*format == 'l') {
                        format++;
                        if (*format == 'x') {
                            /* 10進数を16進数の文字列にする */
                            UINT16 wbuf[200];
                            char tmp[200];
                            unsigned long long num = va_arg(args, unsigned long long);
                            hex_gen(wbuf, num, length);
                            text_gen(tmp, sizeof(tmp), "%-ls", wbuf);
                            while (*arg_str && dest < end) {
                                *dest = *arg_str;
                                dest++;
                                arg_str++;
                            }
                            format++;
                        };
                    };
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

/* OKを緑で表示 */
void PrintOK(EFI_SYSTEM_TABLE *SystemTable) {
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x02); /* 緑で、OKを表示 */
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"[ OK ]");
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x0F); /* 白に戻す */
};

void PrintWarn(EFI_SYSTEM_TABLE *SystemTable) {
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x0E); /* 黄色で、Warnを表示 */
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"[ Warn ]");
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x0F); /* 白に戻す */
};

void PrintError(EFI_SYSTEM_TABLE *SystemTable) {
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x04); /* あかで、Errorを表示 */
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"[ Error ! ]");
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x0F); /* 白に戻す */
};