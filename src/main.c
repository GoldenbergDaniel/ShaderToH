#include <sys/dir.h>
#include <stdio.h>

#include "base_common.h"
#include "base_arena.h"
#include "base_string.h"

typedef struct dirent DIRENT;

#define INPUTS_PATH "res/shader/"
#define OUTPUT_PATH "src/gfx/shaders.h"
#define MAX_LINES 512
#define BUF_SIZE 128

static void read_file(FILE *file, String container[], Arena *arena);
static String gen_var_name(i8 *file_name, String suffix, Arena *arena);

i32 main(void)
{
  Arena arena = arena_create(MiB(1));
  DIR *inputs_dir = opendir(INPUTS_PATH);
  ASSERT(inputs_dir);

  // Clear output
  FILE *file = fopen(OUTPUT_PATH, "w");
  ASSERT(file);
  fputs("", file);

  for (DIRENT *d; (d = readdir(inputs_dir));)
  {
    String file_name = {d->d_name, d->d_namlen};
    
    if (!str_contains(file_name, str(".glsl"))) continue;

    String path = str(INPUTS_PATH);
    path = str_concat(path, file_name, &arena);
    path = str_nullify(path, &arena);
    file = freopen(path.str, "r", file);

    String lines[MAX_LINES] = {0};
    read_file(file, lines, &arena);
    file = freopen(OUTPUT_PATH, "a", file);
    ASSERT(file);

    u16 i = 0;

    fputs("#pragma once\n\n", file);

    // Vertex shader
    String shader_var = gen_var_name(d->d_name, str("_VERT_SRC = \""), &arena);
    fwrite(shader_var.str, 1, shader_var.len, file);

    for (; !str_contains(lines[i], str("@Fragment")) && lines[i].str; i++)
    {
      if (str_contains(lines[i], str("@Vertex"))) continue;

      fwrite(lines[i].str, 1, lines[i].len, file);
      fputs(" ", file);
    }

    fputs("\";\n", file);

    // Fragment shader
    shader_var = gen_var_name(d->d_name, str("_FRAG_SRC = \""), &arena);
    fwrite(shader_var.str, 1, shader_var.len, file);

    for (; lines[i].str != NULL; i++)
    {
      if (str_contains(lines[i], str("@Fragment"))) continue;

      fwrite(lines[i].str, 1, lines[i].len, file);
      fputs(" ", file);
    }

    fputs("\";\n\n", file);
    arena_clear(&arena);
  }

  return 0;
}

static
void read_file(FILE *file, String container[], Arena *arena)
{
  Arena scratch = arena_get_scratch(arena);
  String buf = str_create(BUF_SIZE, &scratch);

  u32 i = 0;
  while (fgets(buf.str, BUF_SIZE, file) != NULL)
  {
    buf.len = cstr_len(buf.str) - 1;
    String line = str_copy(buf, &scratch);

    if (str_equals(line, str("\n"))) continue;
    
    container[i] = str_copy(line, arena);
    container[i] = str_strip_back(container[i], str("\n"));

    i32 comment_pos = str_find(container[i], str("//"), 0, 999);
    if (comment_pos != -1 && !str_contains(container[i], str("// @")))
    {
      container[i] = str_substr(container[i], 0, comment_pos);
    }

    i++;
  }

  arena_clear(&scratch);
}

static
String gen_var_name(i8 *file_name, String suffix, Arena *arena)
{
  i32 delimiter_pos = str_find_char(str(file_name), '.', 0, 999);
  String name = str_substr(str(file_name), 0, delimiter_pos);
  String shader_var = str("const char *");
  shader_var = str_concat(shader_var, name, arena);
  shader_var = str_concat(shader_var, suffix, arena); 

  return shader_var;
}
