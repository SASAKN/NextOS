#include <stdio.h>
#include "font.h"

// ビットをテキストで表示
void display_bit(unsigned char byte, int bit) {
    putchar((byte & (1 << bit)) ? '*' : '.');
}

// フォント表示関数
void display_font(const struct bitmap_font* font, unsigned short character) {
    int charIndex = -1;

    // 指定された文字のインデックスを検索
    for (int i = 0; i < font->Chars; ++i) {
        if (font->Index[i] == character) {
            charIndex = i;
            break;
        }
    }

    // 文字が見つかった場合、ビットマップを表示
    if (charIndex != -1) {
        int charWidth = font->Widths[charIndex];
        const unsigned char* charBitmap = font->Bitmap + charIndex * ((font->Width * font->Height + 7) / 8);

        // ビットマップを表示
        for (int y = 0; y < font->Height; ++y) {
            for (int x = 0; x < charWidth; ++x) {
                display_bit(charBitmap[y * ((font->Width + 7) / 8) + (x / 8)], 7 - (x % 8));
            }
            putchar('\n');
        }
    } else {
        // 文字が見つからなかった場合のエラーメッセージ
        printf("Character U+%04X not found in the font.\n", character);
    }
}

int main() {
    // 表示する文字のコードポイント（ここでは 'A' のU+0041を指定）
    unsigned short charCode = 0x3042;

    // フォントを表示
    display_font(&font, charCode);

    return 0;
}