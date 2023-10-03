#include <sys/dir.h>
#include <stdio.h>

#include "base_common.h"
#include "base_arena.h"
#include "base_string.h"

typedef struct dirent DIRENT;

#define INPUTS_PATH "input/"
#define OUTPUT_PATH "output/shaders.h"
#define MAX_LINES 512 
#define BUF_SIZE 128

void read_shader(FILE *file, String container[], Arena *arena);

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

    String path = str_lit(INPUTS_PATH);
    path = str_concat(path, file_name, &arena);
    path = str_concat(path, STR_NULL, &arena);

    String lines[MAX_LINES] = {0};
    file = freopen(path.str, "r", file);
    read_shader(file, lines, &arena);
    file = freopen(OUTPUT_PATH, "a", file);
    ASSERT(file);

    i32 i = 0;

    // Vertex shader
    fputs("const char *v_shader_src = \"", file);

    for (; !str_contains(lines[i], str_lit("@Fragment")) && lines[i].str; i++)
    {
      if (str_contains(lines[i], str_lit("@Vertex"))) continue;

      fputs(lines[i].str, file);
      fputs(" ", file);
    }

    fputs("\";\n", file);

    // Fragment shader
    fputs("const char *f_shader_src = \"", file);

    for (; lines[i].str != NULL; i++)
    {
      if (str_contains(lines[i], str_lit("@Fragment"))) continue;

      fputs(lines[i].str, file);
      fputs(" ", file);
    }

    fputs("\";\n\n", file);

    arena_clear(&arena);
  }

  printf("Parsed %i files!\n", file_count);

  return 0;
}

void read_shader(FILE *file, String container[], Arena *arena)
{
  Arena scratch = arena_get_scratch((Arena **) {&arena}, 1);
  String buf;
  buf.str = arena_alloc(&scratch, BUF_SIZE);

  u32 i = 0;  
  while (fgets(buf.str, BUF_SIZE, file) != NULL)
  {
    buf.len = cstr_len(buf.str);

    str_strip(&buf, '\0');

    if (str_equals(buf, str_lit("\n"))) continue;

    container[i].str = arena_alloc(arena, buf.len);
    container[i].len = buf.len;
    str_copy(&container[i], buf);
    str_strip(&container[i], '\n');

    i++;
  }

  arena_clear(&scratch);
}
