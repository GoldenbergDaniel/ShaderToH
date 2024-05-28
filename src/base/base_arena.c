#include <stdio.h>
#include <assert.h>

#include "base_common.h"
#include "base_os.h"
#include "base_arena.h"

#ifndef SCRATCH_SIZE
#define SCRATCH_SIZE MiB(64)
#endif

#define ARENA_ALIGN_SIZE 8

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

static inline
u8 *_arena_align_ptr(u8 *ptr, int32_t align, int32_t *offset)
{
	uintptr_t result = (uintptr_t) ptr;
	int32_t modulo = result & ((uintptr_t) (align) - 1);
	if (modulo != 0)
  {
    *offset = align - modulo;
		result += *offset;
	}

	return (u8 *) result;
}

void *arena_alloc(Arena *arena, u64 size)
{
  assert(arena->size >= arena->used + size + ARENA_ALIGN_SIZE);

  u8 *allocated = arena->memory + arena->used;
  i32 offset = 0;
  allocated = _arena_align_ptr(allocated, ARENA_ALIGN_SIZE, &offset);
  arena->used += size + offset;
  
  return allocated;
}

void arena_free(Arena *arena, u64 size)
{
  assert(arena->used - size >= 0);

  arena->used -= size;
}

void arena_clear(Arena *arena)
{
  arena->used = 0;
}

Arena arena_get_scratch(Arena *conflict)
{
  thread_local static Arena scratch_1;
  thread_local static Arena scratch_2;
  thread_local static bool init = TRUE;

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
