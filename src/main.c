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
String gen_var_name(i8 *file_name, String suffix, Arena *arena);

i32 main(void)
{
  Arena arena = arena_create(MEGABYTES(1));
  u64 total_heap = 0;
  DIR *inputs_dir = opendir(INPUTS_PATH);
  ASSERT(inputs_dir);

  // Clear output
  FILE *file = fopen(OUTPUT_PATH, "w");
  fputs("", file);

  i16 file_count = 0;
  for (DIRENT *d; (d = readdir(inputs_dir)); file_count++)
  {
    String file_name = {d->d_name, d->d_namlen};
    
    // Ignore files
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

    u16 i = 0;

    // Vertex shader
    String shader_var = gen_var_name(d->d_name, str_lit("_vert_src = \""), &arena);
    fputs(shader_var.str, file);

    for (; !str_contains(lines[i], str_lit("@Fragment")) && lines[i].str; i++)
    {
      if (str_contains(lines[i], str_lit("@Vertex"))) continue;

      fputs(lines[i].str, file);
      fputs(" ", file);
    }

    fputs("\";\n", file);

    // Fragment shader
    shader_var = gen_var_name(d->d_name, str_lit("_frag_src = \""), &arena);
    fputs(shader_var.str, file);

    for (; lines[i].str != NULL; i++)
    {
      if (str_contains(lines[i], str_lit("@Fragment"))) continue;

      fputs(lines[i].str, file);
      fputs(" ", file);
    }

    fputs("\";\n\n", file);

    total_heap += arena.used;
    arena_clear(&arena);
  }

  printf("Heap: %lu bytes\n", total_heap);
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

String gen_var_name(i8 *file_name, String suffix, Arena *arena)
{
  i64 delimiter_loc = str_find_char(str_lit(file_name), '.');
  String name = str_substr(str_lit(file_name), 0, delimiter_loc, arena);
  String shader_var = str_lit("const char *");
  shader_var = str_concat(shader_var, name, arena);
  shader_var = str_concat(shader_var, suffix, arena); 

  return shader_var;
}
