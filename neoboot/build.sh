#!/bin/bash

source /Users/kenta/.profile
llvm
clang -target x86_64-pc-win32-coff -mno-red-zone -mno-stack-arg-probe -fno-stack-protector -fshort-wchar -Wall -c neoboot.c mem.c func.c
lld-link /subsystem:efi_application /entry:EfiMain /out:boot.efi neoboot.o mem.o func.o