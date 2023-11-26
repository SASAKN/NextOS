#!/bin/zsh

# Move to Mac

script_dir="$(dirname "$(readlink -f "$0")")"

cp /Users/kenta/edk2/Build/NeoBootX64/DEBUG_CLANGPDB/X64/Loader.efi ${script_dir}/loader.efi