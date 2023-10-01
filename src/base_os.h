#pragma once

#include "base_common.h"

#define OS_PROT_NONE 0x00  // PROT_NONE
#define OS_PROT_READ 0x01  // PROT_READ
#define OS_PROT_WRITE 0x02 // PROT_WRITE
#define OS_PROT_EXEC 0x04  // PROT_EXEC

// #define OS_MAP_SHARED 0x0001  // MAP_SHARED
// #define OS_MAP_PRIVATE 0x0002 // MAP_PRIVATE
// #define OS_MAP_FIXED 0x0010   // MAP_FIXED

// @Memory =====================================================================

void *os_alloc(u64 size);
void *os_alloc_file(i32 file, u64 size, i32 offset);
i32 os_set_prot(void *ptr, u64 size, i32 flags);
void os_free(void *ptr, u64 size);

// @Files ======================================================================

typedef struct OS_File OS_File;
struct OS_File
{

};

