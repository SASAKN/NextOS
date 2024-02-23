#include <neos/types.h>
#include "include/proto.h"
#include "include/graphics.h"
#include "include/font.h"

//文字コードの取得
uint16_t get_font(const char *character) {
    unsigned char byte1 = character[0];

    if (byte1 <= 0x7F) {
        // ASCII文字の場合
        return byte1;
    } else if (byte1 >= 0xC0 && byte1 <= 0xDF) {
        // 2バイト文字の場合
        return ((byte1 & 0x1F) << 6) | (character[1] & 0x3F);
    } else if (byte1 >= 0xE0 && byte1 <= 0xEF) {
        // 3バイト文字の場合
        return ((byte1 & 0xF) << 12) | ((character[1] & 0x3F) << 6) | (character[2] & 0x3F);
    } else if (byte1 >= 0xF0 && byte1 <= 0xF7) {
        // 4バイト文字の場合
        return ((byte1 & 0x7) << 18) | ((character[1] & 0x3F) << 12) | ((character[2] & 0x3F) << 6) | (character[3] & 0x3F);
    } else {
        // それ以外の場合、エラーとして0を返す
        return 0;
    }
}

// ビットを処理し、バイナリナンバーで返す
void bin2binary(unsigned char byte, int bit, char* array, int* index) {
    array[(*index)++] = (byte & (1 << bit)) ? '1' : '0';
}

// Unicodeをビットマップにする
uint32_t unicode2bitmap(const char* character, const struct bitmap_font *font, char* array) {
    // Unicode番号の取得
    const uint16_t unicode_num = get_font(character);

    // カウンター
    int char_index = -1;
    int result_index = 0;

    // エラーチェック
    if (unicode_num == 0) {
        return 1;
    }

    // 指定された文字のインデックスを検索
    for (int i = 0; i < font->Chars; ++i) {
        if (font->Index[i] == unicode_num) {
            char_index = i;
            break;
        }
    }

    //文字コードを検索した結果
    if (charIndex != -1) {
        int charWidth = font->Widths[char_index];
        const unsigned char* char_bitmap = font->Bitmap + char_index * ((font->Width * font->Height + 7) / 8);

        // ビットマップを処理
        for (int y = 0; y < font->Height; ++y) {
            for (int x = 0; x < charWidth; ++x) {
                bit2binary(char_bitmap[y * ((font->Width + 7) / 8) + (x / 8)], 7 - (x % 8), array, &result_index);
            }
            //改行の追加
            array[result_index++] = '\n'
        }
    } else {
        return 1;
    }

    return 0;
}