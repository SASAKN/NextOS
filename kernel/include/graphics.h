#pragma once
#include <neos/types.h>

// Graphics Color
#define COLOR_CONSOLE_BG {0x00, 0x00, 0x00}
#define COLOR_CONSOLE_TEXT {0xff, 0xff, 0xff}
#define COLOR_CONSOLE_ERR {0xff, 0x00, 0x00}
#define COLOR_CONSOLE_WARN {0xff, 0xff, 0x00}
#define COLOR_CONSOLE_DEB {0x00, 0xff, 0xff}

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

// Frame Buffer
typedef struct _color {
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
