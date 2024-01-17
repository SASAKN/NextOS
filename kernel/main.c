#include "graphics.h"
#include "bp.h"

//この関数がジャンプされてすぐに実行される
void kernel_main(struct _boot_param *bp) {
    //白く塗りつぶしてみるか
    unsigned char *fb = (unsigned char *)bp->fb_setting.base_addr;
    for( unsigned long long i = 0; i < bp->fb_setting.fb_size; i++ ) {
        fb[i] = 255;
    }
    while(1);
};

