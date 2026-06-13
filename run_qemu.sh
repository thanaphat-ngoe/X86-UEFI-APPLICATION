#!/bin/bash

# ==========================================
# QEMU Runner Script for UEFI OS Installer
# ==========================================

if [ ! -f "nvme0.img" ]; then
    echo "❌ Cannot find nvme0.img, creating a new 10GB image..."
    qemu-img create -f raw nvme0.img 10G
fi

if [ ! -f "nvme1.img" ]; then
    echo "❌ Cannot find nvme1.img, creating a new 10GB image..."
    qemu-img create -f raw nvme1.img 10G
fi

if [ ! -d "VirtualUSB/EFI/BOOT" ]; then
    echo "❌ Cannot find VirtualUSB/EFI/BOOT directory"
    exit 1
fi

if [ ! -f "/usr/share/ovmf/OVMF.fd" ]; then
    echo "❌ Cannot find OVMF Firmware (UEFI BIOS)"
    echo "💡 Please install it with: sudo apt install ovmf"
    exit 1
fi

echo "🚀 Running QEMU-X86-64 Emulation"

qemu-system-x86_64 \
  	-machine q35 \
    -bios /usr/share/ovmf/OVMF.fd \
    -m 2G \
    -vga std \
    -device qemu-xhci,id=usb_bus \
    -drive file=fat:rw:./VirtualUSB,format=raw,if=none,id=drv_usb \
    -device usb-storage,bus=usb_bus.0,drive=drv_usb \
    -drive file=nvme0.img,format=raw,if=none,id=drv_nvme0 \
    -device nvme,drive=drv_nvme0,serial=nvme_serial_0 \
    -drive file=nvme1.img,format=raw,if=none,id=drv_nvme1 \
    -device nvme,drive=drv_nvme1,serial=nvme_serial_1
