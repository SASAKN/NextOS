#include <neos/types.h>
#include "include/proto.h"
#include "include/graphics.h"

//マイクロカーネルのため、これは、ユーザーモードで実行されるようにいつかなります。
// しばらくの間は、カーネルモードで、FBを実行するようにします。
// BootFSに対応したら、FBをユーザーモードで実行します


// Write Pixel
void write_pixel(const fb_config *fb_con, uint32_t x, uint32_t y, const fb *fb) {
    const uint32_t pixel_position = fb_con->pixels_per_scan_line * y + x;
    // PixelRedGreenBlueReserved8BitPerColor
    if (fb_con->pf == efi_rgb) {
        unsigned char *pixel = &fb_con->base[4 * pixel_position];
        pixel[0] = fb->r; // RED
        pixel[1] = fb->g; // GREEN
        pixel[2] = fb->b; // BLUE
    } else if (fb_con->pf == efi_bgr) {
        // PixelBlueGreenRedReserved8BitPerColor
        unsigned char *pixel = &fb_con->base[4 * pixel_position];
        pixel[0] = fb->b; // BLUE
        pixel[1] = fb->g; // GREEN
        pixel[2] = fb->r; // RED
    } else if (fb_con->pf == efi_unknown) {
        halt();
    }
    //他にもpixel_formatはあるが実装していない
}

