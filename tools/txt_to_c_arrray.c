
// Header File
#include <stdio.h>
#include <string.h>

int main() {
    FILE *font_txt;
    FILE *font_c;
    char str1[] = "char font[256][16] =  {\n"; //宣言部
    char str2[] = "    {";
    char str3[] = "}\n";
    char str4[] = "\n};"; //終わり
    char buffer[256] = {0};
    char wbuffer[256] = {0};
    char filename_txt[50];
    char filename_c[50];
    int d;

    //ファイル名を聞く
    printf("テキストファイル名を入力 :");
    scanf("%s", filename_txt);

    //読み取り専用モードでファイルを開く
    if ( (font_txt = fopen(filename_txt, "r")) == NULL ) {
        printf("[ ERROR ] could not open the file");
        return 0;
    }

    //ファイル名を聞く
    printf("Cコードのファイル名を入力 :");
    scanf("%s", filename_c);

    //フォントのファイルを作成する
    if ( (font_c = fopen(filename_c, "w")) == NULL ) {
        printf("[ EROOR ] could not create the file");
        return 0;
    }

    //最初の宣言を書き込む
    fwrite(str1, sizeof(char), strlen(str1), font_c);

    //テキストファイルから行を取得し、書き込む
    fgets(buffer, sizeof(buffer), font_txt);
    for (int k = 0; k < 256; k++) {
        //２次元配列の宣言部を書き込み
        fwrite(str2, sizeof(char), strlen(str2), font_c);
        for (int i = 0; i < 2; i++) {
            fgets(buffer, sizeof(buffer), font_txt);
        }
        for (int i = 0; i < 16; i++) {
            d = 0;
            fgets(buffer, sizeof(buffer), font_txt);
            for (int j = 0; j < 8; j++) {
                //もしbuffer[j]が*ならば
                if(buffer[j] == '*'){
                    //dに対応するビットを割り当て
                    d |= (1 << (8 - j - 1));
                }
            }

            sprintf(wbuffer, "0x%02x, ", d);

            //行最後と配列の最後の特別な処理
            if (k == 255 && i == 15) {
                fwrite(wbuffer, 1, 4, font_c);
            } else if (i == 15) {
                fwrite(wbuffer, 1, 4, font_c);
            } else  {
                fwrite(wbuffer, 1, 6, font_c);
            }
        }
        //2次元配列の最後を書き込み
        fwrite(str3, sizeof(char), strlen(str3), font_c);
    }

    //ファイルの最後を追加
    fwrite(str4, sizeof(char), strlen(str4), font_c);

    //ファイルをクローズ
    fclose(font_txt);
    fclose(font_c);

    //終了
    return 0;
}

