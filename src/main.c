#include <sys/dir.h>
#include <stdio.h>

#include "base_common.h"
#include "base_memory.h"

#include "base_string.h"

#define BUFFER_SIZE 256

typedef struct dirent Dirent;

void read_file(FILE *stream, String container[], u32 count, Arena *arena);

i32 main(void)
{
  Arena arena = arena_create(1024);
  DIR *inputs_dir = opendir("input");
  ASSERT(inputs_dir);

  u8 count = 0;
  for (Dirent *f; (f = readdir(inputs_dir));)
  {
    String file_name = {f->d_name, f->d_namlen};

    if (str_equals(file_name, str_lit(".")) ||
        str_equals(file_name, str_lit("..")) )
      continue;

    String lines[BUFFER_SIZE] = {0};
    String path = str_lit("input/");
    path = str_concat(path, file_name, &arena);
    path = str_concat(path, str_lit("\0"), &arena);

    FILE *file = fopen(path.str, "r");
    read_file(file, lines, BUFFER_SIZE, &arena);
    file = freopen("output/shaders.h", "a+", file);
    ASSERT(file);

    fputs("const char *shader = \"", file);

    for (u32 i = 0; lines[i].str; i++)
    {
      fputs(lines[i].str, file);
    }

    fputs("\";\n", file);

    arena_clear(&arena);
    count++;
  }

  printf("Parsed %i files!\n", count);

  return 0;
}

void read_file(FILE *stream, String container[], u32 count, Arena *arena)
{
  Arena scratch = get_scratch((Arena **) {&arena}, 1);
  String buf = {0};
  buf.str = arena_alloc(&scratch, BUFFER_SIZE);

  u32 i = 0;
  while (fgets(buf.str, BUFFER_SIZE, stream))
  {
    if (i == count) break;

    buf.len = cstr_len(buf.str);

    if (!str_equals(buf, str_lit("\n")) &&
        str_find_substr(buf, str_lit("//")) == -1)
    {
      str_strip(&buf, '\0');
      container[i].str = arena_alloc(arena, buf.len);
      container[i].len = buf.len;
      str_copy(&container[i], buf);
      str_strip(&container[i], '\n');

      i++;
    }
  }

 arena_clear(&scratch);
}
