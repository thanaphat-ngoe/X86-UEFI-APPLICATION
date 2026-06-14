#ifndef EFI_SYSTEM_TABLE_H
#define EFI_SYSTEM_TABLE_H

#include "EFI_CALLING_CONVENTIONS.h"
#include "EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.h"

// UEFI Specification 2.10 Section 4
typedef struct EFI_SYSTEM_TABLE EFI_SYSTEM_TABLE;

// 4.1. UEFI Image Entry Point
    // 4.1.1. EFI_IMAGE_ENTRY_POINT
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_ENTRY_POINT) (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
);

// 4.2. EFI Table Header
    // 4.2.1. EFI_TABLE_HEADER
typedef struct EFI_TABLE_HEADER {
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

// 4.3. EFI System Table
    // 4.3.1. EFI_SYSTEM_TABLE
#define EFI_SYSTEM_TABLE_SIGNATURE      0x5453595320494249
#define EFI_2_100_SYSTEM_TABLE_REVISION ((2<<16) | (100))
#define EFI_2_90_SYSTEM_TABLE_REVISION  ((2<<16) | (90))
#define EFI_2_80_SYSTEM_TABLE_REVISION  ((2<<16) | (80))
#define EFI_2_70_SYSTEM_TABLE_REVISION  ((2<<16) | (70))
#define EFI_2_60_SYSTEM_TABLE_REVISION  ((2<<16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION  ((2<<16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION  ((2<<16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION  ((2<<16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION  ((2<<16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION  ((2<<16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION  ((2<<16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION  ((2<<16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION  ((1<<16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION  ((1<<16) | (02))
#define EFI_SPECIFICATION_VERSION       EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION       EFI_2_100_SYSTEM_TABLE_REVISION

typedef struct EFI_SYSTEM_TABLE {
    EFI_TABLE_HEADER                 Hdr;
    CHAR16                           *FirmwareVendor;
    UINT32                           FirmwareRevision;
    EFI_HANDLE                       ConsoleInHandle;
    VOID                             *ConIn; // EFI_SIMPLE_TEXT_INPUT_PROTOCOL
    EFI_HANDLE                       ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;
    EFI_HANDLE                       StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *StdErr;
    VOID                             *RuntimeServices; // EFI_RUNTIME_SERVICES
    VOID                             *BootServices; // EFI_BOOT_SERVICES
    UINTN                            NumberOfTableEntries;
    VOID                             *ConfigurationTable; // EFI_CONFIGURATION_TABLE
} EFI_SYSTEM_TABLE;

#endif // EFI_SYSTEM_TABLE_H
