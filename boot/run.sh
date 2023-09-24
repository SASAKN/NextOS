#!/bin/bash

# NeoBoot Loader Build Tool 0.1

clang -target x86_64-pc-win32-coff -mno-red-zone -fno-stack-protector -fshort-wchar -Wall -c boot.c
lld-link /subsystem:efi_application /entry:EfiMain /out:boot.efi boot.o
