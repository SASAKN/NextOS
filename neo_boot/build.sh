#!/bin/bash

source /Users/kenta/.profile
llvm
clang -target x86_64-pc-win32-coff -mno-red-zone -mno-stack-arg-probe -fno-stack-protector -fshort-wchar -Wall -c boot.c mem.c efi.c common.c
lld-link /subsystem:efi_application /entry:EfiMain /out:boot.efi boot.o mem.o efi.o common.o kernel.o