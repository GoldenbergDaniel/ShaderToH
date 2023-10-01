#include <stdio.h>

#include "base_common.h"
#include "base_os.h"
#include "base_memory.h"

// @Arena ======================================================================

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
  printf("cleared!\n");
}
