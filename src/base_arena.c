#include <stdio.h>

#include "base_common.h"
#include "base_os.h"
#include "base_arena.h"

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

  i8 *allocated = arena->memory + arena->used;
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

typedef unsigned char bool;

Arena arena_get_scratch(Arena *conflicts[], u8 conflict_count)
{
  static thread_local Arena scratch_1;
  static thread_local Arena scratch_2;
  static thread_local bool init = TRUE;

  if (init)
  {
    scratch_1 = arena_create(MEGABYTES(1));
    scratch_2 = arena_create(MEGABYTES(1));
    init = FALSE;
  }

  Arena result = scratch_1;

  for (u8 i = 0; i < conflict_count; i++)
  {
    Arena *conflict = conflicts[i];

    if (conflicts[i] == &scratch_2)
    {
      result = scratch_2;
    }
    else if (conflict == &scratch_2)
    {
      result = scratch_1;
    }
    else if (conflict == &scratch_1 &&
             conflict == &scratch_2)
    {
      printf("No free scratch arena found!");
      ASSERT(FALSE);
    }
  }

  return result;
}