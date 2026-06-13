#include "efi.h"

EFI_GUID BlockIoGuid = {0x964E5B21, 0x6459, 0x11D2, 0x8E, 0x39, {0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}};

VOID PrintStr(EFI_SYSTEM_TABLE *ST, CHAR16 *Str) {
    ST->ConOut->OutputString(ST->ConOut, Str);
}

VOID PrintHex(EFI_SYSTEM_TABLE *ST, UINT8 Value) {
    CHAR16 Str[3];
    CHAR16 HexChars[] = L"0123456789ABCDEF";
    Str[0] = HexChars[(Value >> 4) & 0x0F]; 
    Str[1] = HexChars[Value & 0x0F];        
    Str[2] = 0;                             
    PrintStr(ST, Str);
}

EFI_STATUS EFIAPI EFI_IMAGE_ENTRY_POINT(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(VOID)ImageHandle;

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    PrintStr(SystemTable, L"--- Minimal UEFI HexDump (Block 0) ---\r\n");

    EFI_STATUS Status;
    UINTN HandleCount = 0;
    EFI_HANDLE *Handles = NULL;

    Status = SystemTable->BootServices->LocateHandleBuffer(
        2,
        &BlockIoGuid,
        NULL,
        &HandleCount,
        &Handles
    );

    if (Status != EFI_SUCCESS) {
        PrintStr(SystemTable, L"Error: No Block IO devices found.\r\n");
        return Status;
    }

    PrintStr(SystemTable, L"Process completed. Halting system...\r\n");
    while (1) {
        // __asm__ __volatile__("hlt");
    }

    return EFI_SUCCESS;
}
