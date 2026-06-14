# ---------------------------------------------------
# Makefile x86_64 UEFI Application 
# (Cross-compiled from Ubuntu ARM64)
# ---------------------------------------------------

CC = x86_64-w64-mingw32-gcc

TARGET = VirtualUSB/EFI/BOOT/BOOTX64.EFI
SRC = EFI.c

CFLAGS = -ffreestanding -mno-red-zone -fshort-wchar -Wall -Wextra -O2

LDFLAGS = -nostdlib -shared -Wl,--subsystem,10 -Wl,-e,EFI_MAIN

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
