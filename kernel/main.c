#include "graphics.h"
#include "bp.h"

//この関数がジャンプされてすぐに実行される
void kernel_main(struct _boot_param bp) {
    //白く塗りつぶしてみるか
    unsigned char *fb = (unsigned char *)bp.fb_setting.base_addr;
    for( unsigned long long i = 0; i < bp.fb_setting.fb_size; i++ ) {
        fb[i] = 255;
    }

    //とりあえず、Printせずにできるもので
    asm volatile (
        "movq %0, %%rax;" // RAXレジスターに値をセット
        : // 出力オペランドはなし
        : "r" (bp.fb_setting.base_addr) // 入力オペランドとして変数valueを指定
        : "%rax" // 破壊されるレジスターを指定
    );
    while(1) __asm__ volatile ("hlt");
};

