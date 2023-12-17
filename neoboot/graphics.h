#pragma once
#include <Uefi/UefiBaseType.h>


enum pixel_format {
    kPixelRGBResv8BitPerColor,
    kPixelBGRResv8BitPerColor,
};


// Frame Buffer
struct fb_configuration {
    unsigned int hr; //水平の画質
    unsigned int vr; //垂直の画質
    unsigned long long fb_size; //フレームバッファーのサイズ
    unsigned long long base_addr; //フレームバッファーへのアドレス
    unsigned int pixels_per_scan_line; // 1ピクセルに必要なバイト数
    enum pixel_format pf; //ピクセルフォーマットの指定
};


EFI_STATUS open_gop(EFI_HANDLE IM, EFI_GRAPHICS_OUTPUT_PROTOCOL **gop);