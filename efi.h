#ifndef EFI_H
#define EFI_H

#include <stdint.h>

#define EFIAPI __attribute__((ms_abi))
#define EFI_SUCCESS 0
#define NULL ((VOID *)0)

typedef uint8_t  BOOLEAN;
typedef int64_t  INTN;
typedef uint64_t UINTN;
typedef int8_t   INT8;
typedef uint8_t  UINT8;
typedef int16_t  INT16;
typedef uint16_t UINT16;
typedef int32_t  INT32;
typedef uint32_t UINT32;
typedef int64_t  INT64;
typedef uint64_t UINT64;
typedef uint16_t CHAR16; // UEFI ใช้ String แบบ 16-bit (UTF-16)
typedef void     VOID;

typedef struct EFI_GUID {
    UINT32 TimeLow;
    UINT16 TimeMid;
    UINT16 TimeHighAndVersion;
    UINT8  ClockSeqHighAndReserved;
    UINT8  ClockSeqLow;
    UINT8  Node[6];
} __attribute__((packed)) EFI_GUID;

typedef VOID *EFI_HANDLE;
typedef UINTN EFI_STATUS;

// --- โครงสร้างพื้นฐานของ UEFI ---
typedef struct {
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

// --- Text Output Protocol (สำหรับ Print) ---
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    VOID *Reset;
    EFI_STATUS (EFIAPI *OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);
    VOID *TestString;
    VOID *QueryMode;
    VOID *SetMode;
    VOID *SetAttribute;
    EFI_STATUS (EFIAPI *ClearScreen)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// --- Boot Services Protocol (สำหรับจัดการ Memory และค้นหาอุปกรณ์) ---
typedef struct EFI_BOOT_SERVICES {
    EFI_TABLE_HEADER Hdr;
    VOID *RaiseTPL; VOID *RestoreTPL;
    VOID *AllocatePages; VOID *FreePages; VOID *GetMemoryMap;
    EFI_STATUS (EFIAPI *AllocatePool)(UINTN PoolType, UINTN Size, VOID **Buffer);
    EFI_STATUS (EFIAPI *FreePool)(VOID *Buffer);
    VOID *CreateEvent; VOID *SetTimer;
    EFI_STATUS (EFIAPI *WaitForEvent)(UINTN NumberOfEvents, VOID **Event, UINTN *Index);
    VOID *SignalEvent; VOID *CloseEvent; VOID *CheckEvent;
    VOID *InstallProtocolInterface; VOID *ReinstallProtocolInterface; VOID *UninstallProtocolInterface;
    EFI_STATUS (EFIAPI *HandleProtocol)(EFI_HANDLE Handle, EFI_GUID *Protocol, VOID **Interface);
    VOID *Reserved; VOID *RegisterProtocolNotify; VOID *LocateHandle; VOID *LocateDevicePath; VOID *InstallConfigurationTable;
    VOID *LoadImage; VOID *StartImage; VOID *Exit; VOID *UnloadImage; VOID *ExitBootServices;
    VOID *GetNextMonotonicCount;
    EFI_STATUS (EFIAPI *Stall)(UINTN Microseconds);
    VOID *SetWatchdogTimer; VOID *ConnectController; VOID *DisconnectController;
    VOID *OpenProtocol; VOID *CloseProtocol; VOID *OpenProtocolInformation; VOID *ProtocolsPerHandle;
    EFI_STATUS (EFIAPI *LocateHandleBuffer)(UINTN SearchType, EFI_GUID *Protocol, VOID *SearchKey, UINTN *NoHandles, EFI_HANDLE **Buffer);
} EFI_BOOT_SERVICES;

// --- System Table (ตัวแปรหลักที่ถูกส่งเข้ามาตอนเริ่มทำงาน) ---
typedef struct {
    EFI_TABLE_HEADER Hdr;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    VOID *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    VOID *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    VOID *ConfigurationTable;
} EFI_SYSTEM_TABLE;

// --- Block IO Protocol (สำหรับอ่าน/เขียน Disk) ---
typedef struct {
    UINT32  MediaId;
    BOOLEAN RemovableMedia;
    BOOLEAN MediaPresent;
    BOOLEAN LogicalPartition;
    BOOLEAN ReadOnly;
    BOOLEAN WriteCaching;
    UINT32  BlockSize;
    UINT32  IoAlign;
    UINT64  LastBlock;
} EFI_BLOCK_IO_MEDIA;

typedef struct EFI_BLOCK_IO_PROTOCOL {
    UINT64 Revision;
    EFI_BLOCK_IO_MEDIA *Media;
    VOID *Reset;
    EFI_STATUS (EFIAPI *ReadBlocks)(struct EFI_BLOCK_IO_PROTOCOL *This, UINT32 MediaId, UINT64 LBA, UINTN BufferSize, VOID *Buffer);
    EFI_STATUS (EFIAPI *WriteBlocks)(struct EFI_BLOCK_IO_PROTOCOL *This, UINT32 MediaId, UINT64 LBA, UINTN BufferSize, VOID *Buffer);
    EFI_STATUS (EFIAPI *FlushBlocks)(struct EFI_BLOCK_IO_PROTOCOL *This);
} EFI_BLOCK_IO_PROTOCOL;

#endif // EFI_H
