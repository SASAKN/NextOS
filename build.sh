# ディレクトリ
script_dir="$(dirname "$(readlink -f "$0")")"

# カーネルパス
KERNEL_PATH=${script_dir}/kernel/kernel.elf

#カーネルソースコードのパス
KERNEL_SOURCE_DIR=${script_dir}/kernel/

# ブートローダーパス
LOADER_PATH=${script_dir}/neoboot/loader.efi

# ビルドディレクトリ
BUILD_DIR=${script_dir}/build

# ボリュームの名前
VOLUME_NAME=NEXTOS

# イメージファイル
IMAGE_PATH=${BUILD_DIR}/nextos.img  # Define IMAGE_PATH before using it

# イメージファイルを作成
function make_image() {
    # DMGファイルの作成 - ${IMAGE_PATH}.dmg
    hdiutil create -size 1g -fs MS-DOS -volname ${VOLUME_NAME} ${IMAGE_PATH}

    # DMGファイルをCDRファイルに変換 - ${IMAGE_PATH}.cdr
    hdiutil convert ${IMAGE_PATH}.dmg -format UDTO -o ${IMAGE_PATH}

    # CDRファイルをIMGファイルに変換 - ${IMAGE_PATH}
    mv ${IMAGE_PATH}.cdr ${IMAGE_PATH}

    # マウント
    hdiutil mount ${IMAGE_PATH}

    # それに移動
    cd /Volumes/${VOLUME_NAME}

    # ファイル構成の作成
    mkdir -p /Volumes/${VOLUME_NAME}/EFI/BOOT

    # EFI/BOOTに移動
    cd /Volumes/${VOLUME_NAME}/EFI/BOOT

    # 移動したら、ファイルを追加
    cp ${LOADER_PATH} /Volumes/${VOLUME_NAME}/EFI/BOOT/BOOTX64.efi

    # ルートフォルダーよりもカーネル
    cp ${KERNEL_PATH} /Volumes/${VOLUME_NAME}/kernel.elf

    # 作業フォルダーに戻る
    cd ${script_dir}

    #作業ファイルの削除
    rm *.img.dmg

    # アンマウント
    hdiutil unmount /Volumes/${VOLUME_NAME} -force
}

# 成功率を増やす関数
function kill_proc() {
    # lsofコマンドでディスクイメージファイルを開いているプロセスを取得し、PIDを抽出
    pids=$(lsof "$IMAGE_PATH" | awk '{if(NR>1)print $2}')

    # 各PIDに対してkillコマンドを実行
    for pid in $pids; do
        kill -9 "$pid"
    done
}

# QEMUで実行する関数
function run_image() {
    qemu-system-x86_64 \
    -m 4G \
    -drive if=pflash,format=raw,file=${BUILD_DIR}/fw/OVMF.fd \
    -drive if=ide,index=0,media=disk,format=raw,file=${BUILD_DIR}/nextos.img \
    -device nec-usb-xhci,id=xhci \
    -device usb-mouse -device usb-kbd \
    -monitor stdio
}

#使い方
function usage() {
    echo ""
    echo "NextOS Build Tools - Help"
    echo "RELEASE リリースとしてビルド"
    echo "DEBUG 詳細なデバッグモード"
    echo ""
}

#クリーン
function trouble() {
    rm -f ${IMAGE_PATH} ${IMAGE_PATH}.dmg
}

#カーネルのビルド
function build_kernel() {
    #カーネルのビルド
    clang -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fshort-wchar -fno-rtti -I ../include/ -c $(cat ${KERNEL_SOURCE_DIR}/complile_file.list)
    ld.lld --entry kernel_main -z norelro --image-base 0x100000 --static -o ${KERNEL_PATH} $(cat ${KERNEL_SOURCE_DIR}/objs_file.list)

    #ビルドエラーのチェック
    if [$? = 0]; then
        rm $(cat ${KERNEL_SOURCE_DIR}/objs_file.list)
    else 
        echo -e "\e[31m[ ERROR ]"
        echo -e "\e[37m Failed to build the kernel"
        exit
    fi
}

while (( $# > 0 ))
do
  case $1 in
    release | RELEASE)
      echo -e "\e[32m[RELEASE] RELEASE VERSION"
      echo -e "\e[37m"
      make_image
      kill_proc
      run_image
      ;;
    help | HELP)
        usage
        ;;
    clean | trouble | CLEAN | TROUBLE)
        trouble
        echo "削除完了"
        ;;
    *)
      usage
      ;;
  esac
  shift
done
