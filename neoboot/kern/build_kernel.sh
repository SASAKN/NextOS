#!/bin/bash

# Kernel Build Tool

# カーネルをビルドします。

clang -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -c ${1}
ld.lld --entry KernelMain -z norelro --image-base 0x100000 --static -o kernel.elf kernel.o
mv kernel.elf ../kernel.elf
