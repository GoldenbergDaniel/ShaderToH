#include <stdio.h>

#include "base_common.h"
#include "base_os.h"
#include "base_arena.h"

#ifndef SCRATCH_SIZE
#define SCRATCH_SIZE MEGABYTES(4)
#endif

Arena arena_create(u64 size)
{
  Arena arena;
  arena.memory = os_alloc(size);
  arena.size = size;
  arena.used = 0;

  return arena;
}

void arena_destroy(Arena *arena)
{
  os_free(arena->memory, arena->size);
  arena->memory = NULL;
  arena->size = 0;
  arena->used = 0;
}

void *arena_alloc(Arena *arena, u64 size)
{
  ASSERT(arena->size >= arena->used + size);

  byte *allocated = arena->memory + arena->used;
  arena->used += size;
  
  return allocated;
}

void arena_free(Arena *arena, u64 size)
{
  ASSERT(arena->used - size >= 0);

  arena->used -= size;
}

void arena_clear(Arena *arena)
{
  arena->used = 0;
}

Arena arena_get_scratch(Arena *conflict)
{
  static THREAD_LOCAL Arena scratch_1;
  static THREAD_LOCAL Arena scratch_2;
  static THREAD_LOCAL bool init = TRUE;

  if (init)
  {
    scratch_1 = arena_create(SCRATCH_SIZE);
    scratch_2 = arena_create(SCRATCH_SIZE);
    init = FALSE;
  }

  Arena scratch = scratch_1;
  if (conflict == &scratch_1) scratch = scratch_2;
  else if (conflict == &scratch_2) scratch = scratch_1;

  return scratch;
}
