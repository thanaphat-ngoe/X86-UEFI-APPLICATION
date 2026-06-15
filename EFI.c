#include "EFI.h"

EFI_STATUS EFI_MAIN(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(VOID)ImageHandle;
    
	UINTN SystemMaxColumns, SystemMaxRows;

	SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
	
	EFI_STATUS Status = SystemTable->ConOut->QueryMode(
		SystemTable->ConOut, 
		SystemTable->ConOut->Mode->Mode, 
		&SystemMaxColumns, 
		&SystemMaxRows
	);

	(VOID)Status;

	UINTN CursorColumn = (SystemMaxColumns - 98) / 2;
	UINTN CursorRow = (SystemMaxRows - 20) / 2;

	SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, CursorColumn, CursorRow - 2);
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"------------------------------LINUX INSTALLER (UEFI SYSTEM) PROJECT!------------------------------");

    SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, CursorColumn, CursorRow);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"┌────────────────────────────────────────────────────────────────────────────────────────────────┐");
	SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, CursorColumn, CursorRow + 1);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"│ Drive 0 Unallocated Space                                                                      │");
	SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, CursorColumn, CursorRow + 2);
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"│ Drive 1 Unallocated Space                                                                      │");
	for (UINTN i = 0; i < 16; i++) 
	{
	SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, CursorColumn, CursorRow + 3 + i);
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"│                                                                                                │");
	}
	SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, CursorColumn, CursorRow + 19);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"└────────────────────────────────────────────────────────────────────────────────────────────────┘");

	while (1) {}
    
	return EFI_SUCCESS;
}
