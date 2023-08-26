# Neox

Neox is a operating system like Unix.

## Kernel

カーネルフォルダーには、アーキテクチャー非依存のファイルがあります。

## Arch

アーキテクチャーフォルダーには、アーキテクチャー依存があるファイルがあります。

## Drivers

OSの第二階層に当たるドライバーのためのソースがあるディレクトリーです。

## Syscall

システムコールの中でも、カーネルコールの実装のソースコードが置いてあるディレクトリーです。

## Setup

Linuxの中では、"Init"と呼ばれているシステムのようなものです。

## Servers

マイクロカーネルで実装しているため、ファイルシステムのソースコードなどは、ここに置くことになります。

## Boot

EDK2で書かれているNeoxのブートローダーです。
ELFで出力されたファイルを開いて、OSを起動させています。

## Include

"#include<neox/config.h>"のように、Includeで、カーネルなどから読み出されるファイルが置いてあります。

## 注意

カーネルコールは、500までです。それ以上書くと、パニックモードになります。
システムがパニックになると、エラーが表示され、起動できなくなります。

## パニック

パニックになると、エラーが表示されて、全く動かなくなります。
パニックになった時は、"kernel/panic.c"の中にある、ファイルを読み、Panicを無視するオプションをTRUEにしてください。
Panicを無視すると、システムが異常を検知できなくなります。

## 以上

これ以外のファイルは、ソースコードを読んで自分で頑張って読み解いてください。
