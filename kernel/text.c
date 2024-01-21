#include <neos/types.h>
#include "include/proto.h"
#include "include/graphics.h"
#include "include/font.h"

//font.oにある定数
extern const uint8_t _binary_hankaku_bin_start;
extern const uint8_t _binary_hankaku_bin_end;
extern const uint8_t _binary_hankaku_bin_size;

const uint8_t *get_font(char c) {
    uintptr_t index = 16 * (unsigned int)c;
    if (index >= (uintptr_t)&_binary_hankaku_bin_size) {
        return NULL;
    }
    return &_binary_hankaku_bin_start + index;
}

void write_ascii(const fb_config *fb_con, int x, int y, char c, const fb *fb) {
    const uint8_t *font = get_font(c);
    if (font == NULL) {
        return;
    }
    for (int dy = 0; dy < FONT_SIZE_Y; dy++) {
        for (int dx = 0; dx < FONT_SIZE_X; dx++) {
            if ((font[dy] << dx) & 0x80u) {
                write_pixel(fb_con, x + dx, y + dy, fb);
            }
        }
    }
}