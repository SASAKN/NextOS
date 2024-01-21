#pragma once
#include <neos/types.h>

// Pixel Format
enum pixel_format {
  efi_rgb,
  efi_bgr,
  efi_bit_mask,
  efi_blt_only,
  efi_format_max,
  efi_unknown
};

// Frame Buffer
typedef struct _fb {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} fb;


// Frame Buffer Config
typedef struct _fb_config {
    unsigned int hr; //水平の画質
    unsigned int vr; //垂直の画質
    unsigned long long fb_size; //フレームバッファーのサイズ
    unsigned char *base; //フレームバッファー
    unsigned int pixels_per_scan_line; // 1ピクセルに必要なバイト数
    enum pixel_format pf; //ピクセルフォーマットの指定
} fb_config;
