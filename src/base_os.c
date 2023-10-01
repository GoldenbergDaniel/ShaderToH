#define BACKEND_LIBC
// #define BACKEND_UNIX

#ifdef BACKEND_LIBC
#include <stdlib.h>
#endif

#ifdef BACKEND_UNIX
#include <sys/mman.h>
#define NULL (void *) 0
#endif

#include "base_common.h"
#include "base_os.h"

inline
void *os_alloc(u64 size)
{
  #ifdef BACKEND_LIBC
  return malloc(size);
  #endif

  #ifdef BACKEND_UNIX
  return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
  #endif
}

inline
void *os_alloc_file(i32 file, u64 size, i32 offset)
{
  #ifdef BACKEND_UNIX
  return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, file, offset);
  #endif

  #ifdef BACKEND_LIBC
  return 0;
  #endif
}

inline
i32 os_set_prot(void *ptr, u64 size, i32 flags)
{
  #ifdef BACKEND_LIBC
  return 0;
  #endif

  #ifdef BACKEND_UNIX
  return mprotect(ptr, size, flags);
  #endif
}

inline
void os_free(void *ptr, u64 size)
{
  #ifdef BACKEND_LIBC
  free(ptr);
  #endif

  #ifdef BACKEND_UNIX
  munmap(ptr, size);
  #endif
}
