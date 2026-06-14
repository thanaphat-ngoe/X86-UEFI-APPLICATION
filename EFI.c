#include "EFI.h"

EFI_STATUS EFI_MAIN(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(VOID)ImageHandle;
    
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 0);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello, World!");

    while (1)
    {
        /* code */
    }
    

    // return 0;
}
