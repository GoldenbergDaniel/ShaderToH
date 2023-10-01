#include <sys/dir.h>
#include <stdio.h>

#include "base_common.h"
#include "base_memory.h"

#include "string.h"

#define BUFFER_SIZE 256

typedef struct dirent Dirent;

void read_file(FILE *stream, String container[], u32 count, Arena *arena);

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

i32 main(void)
{
  Arena arena = arena_create(1024);
  DIR *inputs_dir = opendir("../input");
  ASSERT(inputs_dir);

  printf("Parsed files:\n");

  for (Dirent *f; (f = readdir(inputs_dir));)
  {
    String file_name = {f->d_name, f->d_namlen};

    if (str_equals(file_name, str_lit(".")) ||
        str_equals(file_name, str_lit("..")) )
      continue;

    String path = str_concat(str_lit("../input/"), file_name, &arena);
    str_print(path);
    String lines[BUFFER_SIZE] = {0};
    FILE *file = fopen(path.str, "r");
    read_file(file, lines, BUFFER_SIZE, &arena);
    file = freopen("../output/shaders.h", "a+", file);
    ASSERT(file);

    fputs("const char *shader = \"", file);

    for (u32 i = 0; lines[i].str; i++)
    {
      fputs(lines[i].str, file);
    }

    fputs("\";\n", file);

    // BUG: Creates a seg fault for some reason
    // arena_clear(&arena);
  }

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

//  arena_clear(&scratch);
}
