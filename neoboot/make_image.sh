#!/bin/bash

# Neos Boot Loader Build Tool (UEFI Development)

script_dir="$(dirname "$(readlink -f "$0")")"

#DMGファイルの作成
hdiutil create -size 1g -fs MS-DOS -volname NEOS neos.img

#DMGファイルの名前 neos.img.dmg

#DMGファイルをCDRファイルに変換
hdiutil convert neos.img.dmg -format UDTO -o neos.img

#CDRファイルの名前 neos.img.cdr

#CDRファイルをIMGファイルに変換
mv neos.img.cdr neos.img

#マウント
hdiutil mount neos.img

#それに移動
cd /Volumes/NEOS

#ファイル構成の作成
mkdir -p EFI/BOOT

#さらに、それの階層に移動
cd /Volumes/NEOS/EFI/BOOT

#移動したら、ファイルを追加
cp ${script_dir}/${1} ./BOOTX64.efi

#カーネルもコピー
cp ${script_dir}/kernel.elf /Volumes/NEOS/kernel.elf

#起動スプラッシュもコピー
cp ${script_dir}/splash.png /Volumes/NEOS/splash.png


#作業フォルダーに戻る
cd ${script_dir}

#アンマウント
hdiutil unmount /Volumes/NEOS

#QEMUの実行に移る
source run_image.sh