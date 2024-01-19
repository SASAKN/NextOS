#!/bin/bash

# Kernel Build Tool

script_dir="$(dirname "$(readlink -f "$0")")"

# First, build the kernel file
clang -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -c ${1} -o kernel.o
ld.lld --entry kernel_main -z norelro --image-base 0x100000 --static -o kernel.elf kernel.o

# First Output File : kernel.elf 
# This is the neos kernel file

if [$? = 0]; then
    cp ${script_dir}/kernel.elf ${script_dir}/../neoboot/kernel.elf

# Remove Temporary file
rm kernel.o
