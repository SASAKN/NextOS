def generate_ascii_art(text):
    ascii_art = ""
    for char in text:
        if char.isalnum():  # 英数字の場合
            ascii_art += char
        elif char.isspace():  # 空白文字の場合
            ascii_art += " "
        else:  # それ以外の場合はデフォルトの記号を使用
            ascii_art += "@"

    return ascii_art

if __name__ == "__main__":
    input_text = input("アスキーアートに変換するテキストを入力してください: ")
    result = generate_ascii_art(input_text)
    print(result)
