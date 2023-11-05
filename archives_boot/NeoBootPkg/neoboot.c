// neoboot v.0.01
// neoboootは、elfを読み込み、カーネルに、neobootの構造体を送ります。


/* EDK2で必要なファイルのinclude */
#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/PrintLib.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Protocol/DiskIo2.h>
#include  <Protocol/BlockIo.h>
#include  <Guid/FileInfo.h>

/* 独自Includeファイル */
#include <table.h>
#include <mem.h>
#include <graphics.h>



