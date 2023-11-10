#!/bin/bash

# Create a root file system.

script_dir="$(dirname "$(readlink -f "$0")")"

cd ${script_dir}

# ルートファイルシステムのためのフォルダーを作成

mkdir -p neos/boot
mkdir -p neos/kernel
mkdir -p neos/apps
mkdir -p neos/servers
mkdir -p neos/system
mkdir -p neos/users
mkdir -p neos/etc
mkdir -p neos/appdata
mkdir -p neos/tmp
mkdir -p neos/command
mkdir -p neos/device

cd ${script_dir}/neos/kernel
touch kernel.elf




