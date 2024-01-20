#!/bin/bash

#固定変数(変えると動かなくなります)
script_dir="$(dirname "$(readlink -f "$0")")"

rm *.img *.dmg
rm *.efi *.elf