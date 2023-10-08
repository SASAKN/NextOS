#!/bin/bash

script_dir="$(dirname "$(readlink -f "$0")")"

qemu-system-x86_64 \
    -m 4G \
    -drive if=pflash,format=raw,file=${script_dir}/OVMF.fd \
    -drive if=ide,index=0,media=disk,format=raw,file=${script_dir}/neos.img \
    -device nec-usb-xhci,id=xhci \
    -device usb-mouse -device usb-kbd \
    -monitor stdio 