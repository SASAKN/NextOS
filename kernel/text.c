#include <neos/types.h>
#include "include/proto.h"
#include "include/graphics.h"

//font.oにある定数
extern const _binary_font_bin_start;
extern const _binary_font_bin_end;
extern const _binary_font_bin_size;

const uint8_t *get_font(char c) {
    uintptr_t index = 16 * (unsigned int)c;
    if (index >= (uintptr_t)&_binary_font_bin_size) {
        return NULL;
    }
    return &_binary_font_bin_start + index;
}