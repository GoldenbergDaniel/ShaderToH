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
#define SCRATCH_SIZE KILOBYTES(1)

static void read_file(FILE *file, String container[], Arena *arena);
static String gen_var_name(i8 *file_name, String suffix, Arena *arena);

i32 main(void)
{
  typedef struct Stats Stats;
  struct Stats
  {
    u64 total_heap;
    i16 file_count;
  };

  Stats stats = {0};
  Arena arena = arena_create(MEGABYTES(1));
  DIR *inputs_dir = opendir(INPUTS_PATH);
  ASSERT(inputs_dir);

  // Clear output
  FILE *file = fopen(OUTPUT_PATH, "w");
  fputs("", file);

  for (DIRENT *d; (d = readdir(inputs_dir)); stats.file_count++)
  {
    String file_name = {d->d_name, d->d_namlen};
    
    if (!str_contains(file_name, str_lit(".glsl")))
    {
      stats.file_count--;
      continue;
    }

    String path = str_lit(INPUTS_PATH);
    path = str_concat(path, file_name, &arena);
    path = str_nullify(path, &arena);

    String lines[MAX_LINES] = {0};
    file = freopen(path.str, "r", file);
    read_file(file, lines, &arena);
    file = freopen(OUTPUT_PATH, "a", file);
    ASSERT(file);

    u16 i = 0;

    // Vertex shader
    String shader_var = gen_var_name(d->d_name, str_lit("_vert_src = \""), &arena);
    fputs(shader_var.str, file);

    for (; !str_contains(lines[i], str_lit("@Fragment")) && lines[i].str; i++)
    {
      if (str_contains(lines[i], str_lit("@Vertex"))) continue;

      String nullified = str_nullify(lines[i], &arena);
      fputs(nullified.str, file);
      fputs(" ", file);
    }

    fputs("\";\n", file);

    // Fragment shader
    shader_var = gen_var_name(d->d_name, str_lit("_frag_src = \""), &arena);
    fputs(shader_var.str, file);

    for (; lines[i].str != NULL; i++)
    {
      if (str_contains(lines[i], str_lit("@Fragment"))) continue;

      String nullified = str_nullify(lines[i], &arena);
      fputs(nullified.str, file);
      fputs(" ", file);
    }

    fputs("\";\n\n", file);

    stats.total_heap += arena.used;
    arena_clear(&arena);
  }

  printf("Parsed %i files!\n", stats.file_count);
  printf("Heap: %.2f KB\n", (f32) stats.total_heap / 1024.0f);

  return 0;
}

static
void read_file(FILE *file, String container[], Arena *arena)
{
  Arena scratch = arena_get_scratch(arena);
  String buf = str_new(BUF_SIZE, &scratch);

  u32 i = 0;
  while (fgets(buf.str, BUF_SIZE, file) != NULL)
  {
    buf.len = cstr_len(buf.str);
    str_strip(&buf, '\0');

    if (str_equals(buf, str_lit("\n"))) continue;
    
    container[i] = str_new(buf.len, arena);
    str_copy(&container[i], buf);
    str_strip(&container[i], '\n');

    i64 comment_pos = str_find(container[i], str_lit("//"));
    if (comment_pos != -1 && !str_contains(container[i], str_lit("// @")))
    {
      container[i] = str_substr(container[i], 0, comment_pos, arena);
    }

    i++;
  }

  arena_clear(&scratch);
}

static
String gen_var_name(i8 *file_name, String suffix, Arena *arena)
{
  i64 delimiter_pos = str_find_char(str_lit(file_name), '.');
  String name = str_substr(str_lit(file_name), 0, delimiter_pos, arena);
  String shader_var = str_lit("const char *");
  shader_var = str_concat(shader_var, name, arena);
  shader_var = str_concat(shader_var, suffix, arena); 
  shader_var = str_nullify(shader_var, arena);

  return shader_var;
}
