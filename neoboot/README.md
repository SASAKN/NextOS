# NeoBoot Kernel Param Specification

これは、カーネルパラメーターの仕様です。
これを見て、カーネル設計者は、設計する必要があります。
実は、NeoBootは、カーネル設計者がブートローダーに合わす部分が非常に少ないです。

<kernel_param.h>

```c

//このようなinfoをブートローダーは、いじります。
// この構造体が埋め込まれていないと、ブートローダーは、エラーを起こします.
typedef struct {
    uint32_t vr;
    uint32_t hr;
} frame_buffer_info;

struct your_os_frame_buffer {
    frame_buffer_info info;
    uint64_t r;
    uint64_t g;
    uint64_t b;
};

typedef struct {
    struct your_os_frame_buffer fb;
    struct efi_info efi;
    struct memory_map memmap;
} neoboot_t;

```

コードを書き途中、後で、この仕様のコードは、docsに公開します。
簡単な構造体とデータ型があれば動くので、他のライブラリーに依存する必要などがありません。
