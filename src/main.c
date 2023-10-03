#include <sys/dir.h>
#include <stdio.h>

#include "base_common.h"
#include "base_arena.h"
#include "base_string.h"

typedef struct dirent DIRENT;

#define INPUTS_PATH "input/"
#define OUTPUT_PATH "output/shaders.h"
#define BUFFER_SIZE 256

void read_shader(FILE *stream, String container[], Arena *arena);

i32 main(void)
{
  Arena arena = arena_create(MEGABYTES(1));
  DIR *inputs_dir = opendir(INPUTS_PATH);
  ASSERT(inputs_dir);

  // Clear output
  FILE *file = fopen(OUTPUT_PATH, "w");
  fputs("", file);

  i16 file_count = 0;
  for (DIRENT *d; (d = readdir(inputs_dir)); file_count++)
  {
    String file_name = {d->d_name, d->d_namlen};

    if (str_equals(file_name, str_lit(".")) ||
        str_equals(file_name, str_lit("..")) ||
        str_equals(file_name, str_lit(".DS_Store")))
    {
      file_count--;
      continue;
    }

    String lines[BUFFER_SIZE] = {0};

    String path = str_lit(INPUTS_PATH);
    path = str_concat(path, file_name, &arena);
    path = str_concat(path, STR_NULL, &arena);

    file = freopen(path.str, "r", file);
    read_shader(file, lines, &arena);
    file = freopen(OUTPUT_PATH, "a", file);
    ASSERT(file);

    fputs("const char *shader = \"", file);

    for (u32 i = 0; lines[i].str != NULL; i++)
    {
      str_print(lines[i]);

      if (str_contains(lines[i], str_lit("@Vertex")) ||
          str_contains(lines[i], str_lit("@Fragment")))
        continue;

      fputs(lines[i].str, file);
    }

    fputs("\";\n", file);

    arena_clear(&arena);
  }

  printf("Parsed %i files!\n", file_count);

  return 0;
}

void read_shader(FILE *stream, String container[], Arena *arena)
{
  Arena scratch = arena_get_scratch((Arena **) {&arena}, 1);
  String buf;
  buf.str = arena_alloc(&scratch, BUFFER_SIZE);

  u32 i = 0;  
  while (fgets(buf.str, BUFFER_SIZE, stream) != NULL)
  {
    buf.len = cstr_len(buf.str);

    if (str_equals(buf, str_lit("\n"))) continue;

    str_strip(&buf, '\0');
    container[i].str = arena_alloc(arena, buf.len);
    container[i].len = buf.len;
    str_copy(&container[i], buf);
    str_strip(&container[i], '\n');

    i++;
  }

  arena_clear(&scratch);
}
