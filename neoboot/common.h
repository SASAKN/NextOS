#pragma once
#include <Uefi/UefiBaseType.h>
#include "graphics.h"

void PrintOK(void);
void PrintWarn(void);
void PrintError(void);
EFI_STATUS open_root_dir(EFI_HANDLE IM, EFI_FILE_PROTOCOL **root);
UINT64 open_file_read(EFI_FILE_PROTOCOL *root, CHAR16 *file_path, EFI_FILE_PROTOCOL *file);
void Halt(void);

#define NEOBOOT_VERSION 1

struct _boot_param {
    fb_config fb_setting; //フレームバッファーの設定
    int neoboot_ver; //ブートローダーバージョン
};

//ブートパラメーターの関係性について
//ブートローダーバージョンがないと、カーネルはあ、ブートローダーから送られてきた情報の処理ができなくなる恐れがあります。
//フレームバッファーは、起動時に送られ、画面表示に必要です。