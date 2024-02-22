#ディレクトリ
script_dir="$(dirname "$(readlink -f "$0")")"

#カーネルパス
KERNEL_PATH=${script_dir}/kernel/kernel.elf

#ブートローダーパス
LOADER_PATH=${script_dir}/neoboot/loader.efi

#ビルドディレクトリ
BUILD_DIR=${script_dir}/build

#ボリュームの名前
VOLUME_NAME=NEXTOS

#イメージファイル
IMAGE_PATH=${BUILD_DIR}/nextos.img

#イメージファイルを作成
function make_image() {
    #DMGファイルの作成 - nextos.img.dmg
    hdiutil create -size 1g -fs MS-DOS -volname ${VOLUME_NAME} nextos.img

    #DMGファイルをCDRファイルに変換 - nextos.img.cdr
    hdiutil convert nextos.img.dmg -format UDTO -o nextos.img

    #CDRファイルをIMGファイルに変換 - nextos.img
    mv nextos.img.cdr nextos.img

    #マウント
    hdiutil mount nextos.img

    #それに移動
    cd /Volumes/${VOLUME_NAME}

    #ファイル構成の作成
    mkdir -p EFI/BOOT

    #EFI/BOOTに移動
    cd /Volumes/${VOLUME_NAME}/EFI/BOOT

    #移動したら、ファイルを追加
    cp ${LOADER_PATH} /Volumes/${VOLUME_NAME}/BOOTX64.efi

    #ルートフォルダーよりもカーネル
    cp ${KERNEL_PATH} /Volumes/${VOLUME_NAME}/kernel.elf

    #作業フォルダーに戻る
    cd ${script_dir}

    #アンマウント
    hdiutil unmount /Volumes/${VOLUME_NAME} -force
}

#成功率を増やす関数
function kill_proc() {
    # lsofコマンドでディスクイメージファイルを開いているプロセスを取得し、PIDを抽出
    pids=$(lsof "$IMAGE_PATH" | awk '{if(NR>1)print $2}')

    # 各PIDに対してkillコマンドを実行
    for pid in $pids; do
        kill -9 "$pid"
    done
}

#QEMUで実行する関数
function run_image() {
    qemu-system-x86_64 \
    -m 4G \
    -drive if=pflash,format=raw,file=${BUILD_DIR}/fw/OVMF.fd \
    -drive if=ide,index=0,media=disk,format=raw,file=/${IMAGE_PATH} \
    -device nec-usb-xhci,id=xhci \
    -device usb-mouse -device usb-kbd \
    -monitor stdio
}


function usage() {
    echo "\n"
    echo "NextOS Build Tools - Help"
    echo "RELEASE リリースとしてビルド"
    echo "DEBUG 詳細なデバッグモード"
    echo "\n"
}

function trouble() {
    rm -f ${IMAGE_PATH}
}

while (( $# > 0 ))
do
  case $1 in
    --release | release | RELEASE | -r)
      echo "\e[32m[RELEASE] RELEASE VERSION"
      ;;
    -*)
      echo "invalid option"
      exit 1
      ;;
    --help | h | help)
        usage
        ;;
    *)
      echo "argument $1"
      ;;
  esac
  shift
done