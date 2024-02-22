#ディレクトリ
script_dir="$(dirname "$(readlink -f "$0")")"

#カーネルパス
KERNEL_PATH=${script_dir}/kernel/kernel.elf

#ブートローダーパス
LOADER_PATH=${script_dir}/neoboot/loader.efi

#ビルドディレクトリ
BUILD_DIR=${script_dir}/build

