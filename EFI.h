#ifndef EFI_H
#define EFI_H

#include "EFI_SYSTEM_TABLE.h"

#define EFI_SUCCESS 0
#define EFI_UNSUPPORTED 3
#define EFI_DEVICE_ERROR 7

// typedef struct {
//     UINT32 TimeLow;
//     UINT16 TimeMid;
//     UINT16 TimeHighAndVersion;
//     UINT8  ClockSeqHighAndReserved;
//     UINT8  ClockSeqLow;
//     UINT8  Node[6];
// } __attribute__((packed)) EFI_GUID;

#endif // EFI_H
