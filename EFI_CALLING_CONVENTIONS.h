#ifndef EFI_CALLING_CONVENTIONS_H
#define EFI_CALLING_CONVENTIONS_H

#include <stdint.h>

// UEFI Specification 2.10 Section 2

// 2.3. Calling Conventions
    // 2.3.1. Data Types
typedef uint8_t     BOOLEAN;
typedef int64_t     INTN;
typedef uint64_t    UINTN;
typedef int8_t      INT8;
typedef uint8_t     UINT8;
typedef int16_t     INT16;
typedef uint16_t    UINT16;
typedef int32_t     INT32;
typedef uint32_t    UINT32;
typedef int64_t     INT64;
typedef uint64_t    UINT64;
typedef __int128_t  INT128;
typedef __uint128_t UINT128;
typedef char        CHAR8;    
typedef uint16_t    CHAR16;
typedef void        VOID;

typedef UINTN       EFI_STATUS;
typedef VOID        *EFI_HANDLE;
typedef VOID        *EFI_EVENT;
typedef UINT64      EFI_LBA;
typedef UINTN       EFI_TPL;

#define IN
#define OUT
#define OPTIONAL
#define CONST const
#define EFIAPI __attribute__((ms_abi))

#endif // EFI_CALLING_CONVENTIONS_H
