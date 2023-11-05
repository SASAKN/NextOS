#!/bin/bash

script_dir="$(dirname "$(readlink -f "$0")")"

cd ${script_dir}/

#EFIファイルとオブジェクトファイルの削除
rm *.o
rm *.efi

#実際に起動するイメージを削除
rm *.img.dmg
rm *.img
