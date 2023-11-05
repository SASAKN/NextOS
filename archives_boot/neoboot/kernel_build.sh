#/bin/bash

#Copyright SASAKEN
#For Test.
source /Users/kenta/.profile
llvm
# clang -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -c test_kernel.c
# ld.lld --entry KernelMain -z norelro --image-base 0x100000 --static -o kernel.elf test_kernel.o

# Intel64用のカーネルを作成
nasm test_kernel.asm -o kernel.o