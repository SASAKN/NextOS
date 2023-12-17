#pragma once
#include <Uefi/UefiBaseType.h>


enum pixel_format {
    kPixelRGBResv8BitPerColor,
    kPixelBGRResv8BitPerColor,
};


// Frame buffer configuration
struct fb_configuration {
    UINT32 hr; //水平の画質
    UINT32 vr; //垂直の画質
    EFI_PHYSICAL_ADDRESS base_addr; //フレームバッファーへのアドレス
    UINT32 pixels_per_scan_line; // 1ピクセルに必要なバイト数
    enum pixel_format pf; //ピクセルフォーマットの指定
};


EFI_STATUS open_gop(EFI_HANDLE IM, EFI_GRAPHICS_OUTPUT_PROTOCOL **gop);