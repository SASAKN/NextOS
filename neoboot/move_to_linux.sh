#!/bin/zsh

# Move to Linux

script_dir="$(dirname "$(readlink -f "$0")")"

rsync -av --progress --exclude 'README.md' --exclude '.git/' --exclude '*.img' --exclude '*.dmg' ${script_dir}/ /Users/kenta/edk2/neoboot


