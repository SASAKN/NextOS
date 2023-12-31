#!/bin/bash

# Neos Boot Loader Build Tool (UEFI Development)

script_dir="$(dirname "$(readlink -f "$0")")"

# Usage
function usage() {
    echo "[ Important !! ]NeoBootのビルドツール"
    echo "第一引数に、EFIファイルの名前を入れて実行してください"
    echo "Developerがこれをせず、実行し、neobootディレクトリーをコピーして起動させてしまい、失敗する人がいます"
}

#ルートファイルシステムを作成
usage
source ${script_dir}/make_root_fs.sh

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

#それをコピー
cp -r ${script_dir}/neos/ /Volumes/NEOS/neos/

#ルートフォルダーよりもカーネル
cp ${script_dir}/kernel.elf /Volumes/NEOS/kernel.elf

#作業フォルダーに戻る
cd ${script_dir}

#アンマウント
hdiutil unmount /Volumes/NEOS -force

#QEMUの実行に移る
command ${script_dir}/run_image.sh