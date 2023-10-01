#include <stdio.h>

#include "base_common.h"
#include "base_os.h"
#include "base_memory.h"

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

Arena get_scratch(Arena *conflicts[], u8 conflict_count)
{
  thread_local Arena scratch_1;
  thread_local Arena scratch_2;
  thread_local b8 init = TRUE;

  if (init)
  {
    scratch_1 = arena_create(1024);
    scratch_2 = arena_create(1024);
    init = FALSE;
  }

  Arena scratch = scratch_1;

  for (u8 i = 0; i < conflict_count; i++)
  {
    if (&scratch_1 == conflicts[i])
    {
      scratch = scratch_2;
    }
  }

  return scratch;
}
