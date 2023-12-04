#!/bin/bash

script_dir="$(dirname "$(readlink -f "$0")")"

#    -nographic -serial mon:stdio

# ディスクイメージファイルのパス
image_file="${script_dir}/neos.img"

# lsofコマンドでディスクイメージファイルを開いているプロセスを取得し、PIDを抽出
pids=$(lsof "$image_file" | awk '{if(NR>1)print $2}')

# 各PIDに対してkillコマンドを実行
for pid in $pids; do
  kill -9 "$pid"
done

qemu-system-x86_64 \
    -m 4G \
    -drive if=pflash,format=raw,file=${script_dir}/OVMF.fd \
    -drive if=ide,index=0,media=disk,format=raw,file=${script_dir}/neos.img \
    -device nec-usb-xhci,id=xhci \
    -device usb-mouse -device usb-kbd \
    -nographic -serial mon:stdio

# -monitor stdio　//GUIを使いたい場合

#GUIを使用していないときに、終了したい時はctrl a xで、終了できます