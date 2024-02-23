#include <stdio.h>

int getUnicodeNumber(const char *character) {
    // UTF-8エンコーディングに対応するため、文字列として入力を受け取る
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

int main() {
    char inputCharacter[5]; // 絵文字の場合、最大4バイト（UTF-8） + 1バイト（null終端）を考慮

    printf("文字を入力してください: ");
    scanf("%s", inputCharacter);

    int unicodeNumber = getUnicodeNumber(inputCharacter);

    if (unicodeNumber == 0) {
        printf("エラー: 不正な文字が入力されました。\n");
    } else {
        printf("文字 '%s' のUnicode番号は %x です。\n", inputCharacter, unicodeNumber);
    }

    return 0;
}
