# Neos

Neos is a operating system.

## Kernel

カーネルフォルダーには、アーキテクチャー非依存のファイルがあります。

## Arch

アーキテクチャーフォルダーには、アーキテクチャー依存があるファイルがあります。

## Functions

C言語用の関数などがあります。
このフォルダーがないとOSにあるプログラムは、動かない可能性があります。
OSのコア部分は、これに頼っていないため、動くようになっています。
アプリケーションは、ここから読み込むことも可能です。
ここから読み込むと、C言語の標準ライブラリーを使っているように使えます。
このディレクトリーにファイルを作ると、Includeで、Appが読み込むことができます。

## Drivers

OSの第二階層に当たるドライバーのためのソースがあるディレクトリーです。

## Syscall

システムコールの中でも、カーネルコールの実装のソースコードが置いてあるディレクトリーです。

## Servers

マイクロカーネルで実装しているため、ファイルシステムのソースコードなどは、ここに置くことになります。

## Boot

EDK2で書かれているNeosのブートローダーです。
ELFで出力されたファイルを開いて、OSを起動させています。

## Include

"#include<neos/config.h>"のように、Includeで、カーネルなどから読み出されるファイルが置いてあります。

## 注意

カーネルコールは、500までです。それ以上書くと、パニックモードになります。
システムがパニックになると、エラーが表示され、起動できなくなります。

## パニック

パニックになると、エラーが表示されて、全く動かなくなります。
パニックになった時は、"kernel/panic.c"の中にある、ファイルを読み、Panicを無視するオプションをTRUEにしてください。
Panicを無視すると、システムが異常を検知できなくなります。

## コンセプト

全く新しいOSを目指しています。
Linuxなどと似ていますが、似ていない部分があります。

## クリップボードなどは、ありません

現時点では、実用性をしっかりと意識した実験的OSであるため、まだクリップボードなどがありません。

## 一部C++や、Go、Rustが使われています

Neosは、Go、Rust、C++をたまに使います。

## 以上

これ以外のファイルは、ソースコードを読んで自分で頑張って読み解いてください。
