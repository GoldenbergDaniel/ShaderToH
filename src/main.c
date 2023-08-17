#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "globals.h"
#include "string.h"

#define BUFFER_SIZE 256

void init_lines(String lines[], u32 count);
void read_file(FILE *stream, String container[], u32 count);

i32 main(i32 argc, i8 *argv[])
{
  if (argc < 2)
  {
    printf("Error: No argument provided.\n");
    return 1;
  }
  else if (argc > 2)
  {
    printf("Error: More than one argument provided.\n");
    return 1;
  }

  String path = str_lit(argv[1]);
  FILE *file = fopen(path.data, "r");
  assert(file != NULL);

  String lines[BUFFER_SIZE];
  init_lines(lines, BUFFER_SIZE);
  read_file(file, lines, BUFFER_SIZE);

  freopen("input/shaders.glsl", "a", file);

  fputs("\n", file);
  fputs("const char *shader = \"", file);
  printf("const char *shader = \"");

  for (u32 i = 0; (lines[i].data != NULL); i++)
  {
    fputs(lines[i].data, file);
    printf("%s", lines[i].data);
  }

  fputs("\";", file);
  printf("\";\n");

  return 0;
}

void init_lines(String lines[], u32 count)
{
  for (u32 i = 0; i < count; i++)
  {
    lines[i].data = NULL;
  }
}

void read_file(FILE *stream, String container[], u32 count)
{
  String buf = str_new(NULL, BUFFER_SIZE);
  u32 i = 0;

  while (fgets(buf.data, BUFFER_SIZE, stream) != NULL)
  {
    if (i == count) break;

    buf.len = cstr_len(buf.data);

    if (str_equals(buf, str_lit("\n"))) continue;
    if (str_find_substr(buf, str_lit("//")) != -1) continue;

    str_strip(&buf, '\0');
    container[i].data = (i8 *) malloc(buf.len);
    str_copy(&container[i], buf);
    str_strip(&container[i], '\n');
    
    i++;
  }

  str_free(&buf);
}
