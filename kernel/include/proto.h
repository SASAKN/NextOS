// Prototype Functions
#include <neos/types.h>
#include "graphics.h"

// HAL Functions - これに合わせてHALを設計するべき。
void halt(void);

// Graphics Functions
void write_pixel(const fb_config *fb_con, uint32_t x, uint32_t y, const fb *fb);