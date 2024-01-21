#include <neos/types.h>
#include "graphics.h"

// Text Functions
const uint8_t *get_font(char c);
void write_ascii(const fb_config *fb_con, int x, int y, char c, const fb *fb);

// Graphics Functions
void write_pixel(const fb_config *fb_con, uint32_t x, uint32_t y, const fb *fb);


// HAL Functions