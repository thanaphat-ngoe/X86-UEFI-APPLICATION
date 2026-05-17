#!/bin/sh

# Exit immediately if any command fails
set -e

EFI_FILE="build/BOOTX64.EFI"
BZIMAGE_FILE="build/bzImage"
IMG_FILE="build/DISK.IMG"
VOL_NAME="EFIVOLUME"
VOL_PATH="/Volumes/$VOL_NAME"

echo "--- Checking for executables ---"
if [ ! -f "$EFI_FILE" ]; then
    echo "Error: $EFI_FILE not found! Please build your code first (make)."
    exit 1
fi

if [ ! -f "$BZIMAGE_FILE" ]; then
    echo "Error: $BZIMAGE_FILE not found! Please place your compiled Linux kernel here."
    exit 1
fi

cd src

make

cd ..

echo "--- Creating 64MB disk image ($IMG_FILE) ---"
rm -f "$IMG_FILE"
dd if=/dev/zero of="$IMG_FILE" bs=1m count=64

echo "--- Partitioning and formatting natively on macOS ---"
DISK_DEV=$(hdiutil attach -nomount "$IMG_FILE" | head -n 1 | awk '{print $1}')
diskutil partitionDisk "$DISK_DEV" 1 GPT "MS-DOS FAT32" "$VOL_NAME" 100%

echo "--- Copying BOOTX64.EFI and bzImage ---"
mkdir -p "$VOL_PATH/EFI/BOOT"
cp "$EFI_FILE" "$VOL_PATH/EFI/BOOT/BOOTX64.efi"
cp "$BZIMAGE_FILE" "$VOL_PATH/bzImage"

echo "--- Ejecting Image ---"
diskutil eject "$DISK_DEV"

echo "--- Starting QEMU ---"
qemu-system-x86_64 -bios edk2/Build/OvmfX64/DEBUG_GCC/FV/OVMF.fd -m 16G -vga std -nographic -drive format=raw,file=build/DISK.img
