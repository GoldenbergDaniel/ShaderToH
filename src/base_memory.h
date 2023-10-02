#pragma once

#include "base_common.h"

typedef struct Arena Arena;
struct Arena
{
  i8 *memory;
  u64 size;
  u64 used;
};

#define KILOBYTES(bytes) (bytes << 10)
#define MEGABYTES(bytes) (bytes << 20)
#define GIGABYTES(bytes) (bytes << 30)

// Creates a new Arena with `size` bytes of memory
Arena arena_create(u64 size);
// Frees all memory in the arena
void arena_destroy(Arena *arena);
// Allocates/pushes `size` bytes onto the arena's stack
void *arena_alloc(Arena *arena, u64 size);
// Deallocates/pops `size` bytes from the arena's stack
void arena_free(Arena *arena, u64 size);
// Clears the arena's stack
void arena_clear(Arena *arena);

Arena get_scratch(Arena *conflicts[], u8 conflict_count);
