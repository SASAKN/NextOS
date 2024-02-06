import freetype
import numpy as np

# 変換するTTFフォントファイル名
font_file = "font.ttf"

# 出力するC言語ファイル名
output_file = "output.c"

# フォントサイズ
font_size = 16

# ビットマップフォントの最大幅
max_width = 256

# ビットマップフォントの最大高さ
max_height = 256

# FreeTypeライブラリの初期化
ft = freetype.Library()

# フォントファイルを開く
face = ft.new_face(font_file)

# フォントサイズを設定
face.set_pixel_sizes(font_size, font_size)

# ビットマップフォントの生成
glyph_buffer = freetype.BitmapGlyph()
bitmap = np.zeros((max_height, max_width), dtype=np.uint8)

for char in range(32, 127):
    # 文字コードからグリフを取得
    face.load_char(char, freetype.FT_LOAD_RENDER)

    # グリフのビットマップを取得
    glyph_buffer.bitmap = bitmap
    face.get_glyph(glyph_buffer)

    # ビットマップデータをC言語の配列に変換
    char_data = []
    for row in range(glyph_buffer.bitmap.rows):
        for col in range(glyph_buffer.bitmap.width):
            char_data.append(1 if glyph_buffer.bitmap.buffer[row * glyph_buffer.bitmap.pitch + col] > 0 else 0)

    # C言語のソースコードを生成
    with open(output_file, "w") as f:
        f.write(f"#include <stdint.h>\n\n")
        f.write(f"const uint8_t font_data[{len(char_data)}] = {{\n")
        for i in range(0, len(char_data), 16):
            f.write("    ")
            for j in range(i, min(i + 16, len(char_data))):
                f.write(f"{char_data[j]}, ")
            f.write("\n")
        f.write("};\n")

# 出力ファイル名を出力
print(f"C言語のビットマップフォントデータが生成されました: {output_file}")
