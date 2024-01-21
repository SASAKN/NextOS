#!/bin/bash

# Kernel Build Tool

script_dir="$(dirname "$(readlink -f "$0")")"

# First, build the kernel file
clang -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fshort-wchar -fno-rtti -I ../include/ -c $(cat ${script_dir}/complile_file.list)
ld.lld --entry kernel_main -z norelro --image-base 0x100000 --static -o kernel.elf $(cat ${script_dir}/objs_file.list)

# First Output File : kernel.elf 
# This is the neos kernel file

if [ $? = 0 ]; then
    rm $(cat ${script_dir}/objs_file.list)
    cp ${script_dir}/kernel.elf ${script_dir}/../neoboot/kernel.elf
else
    echo "[ EROOR ] Can not create the kernel file"
fi