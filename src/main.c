#ifdef _WIN32
#include <windows.h>
#define _CRT_SECURE_NO_DEPRECATE
#elif
#include <dirent.h>
#endif
#include <stdio.h>
#include <assert.h>

#include "base/base_common.h"
#include "base/base_arena.h"
#include "base/base_string.h"

#define MAX_FILES 64
#define MAX_LINES 512
#define BUF_SIZE 128
 
typedef struct dirent DIRENT;

static void read_file_into_array(FILE *file, String container[], Arena *arena);
static String gen_var_name(String file_name, String suffix, Arena *arena);
static StringArray file_names_from_dir(String dir_name, String file_ext, Arena *arena);
static StringArray _file_names_from_dir_unix(String dir_name, String file_ext, Arena *arena);
static StringArray _file_names_from_dir_windows(String dir_name, String file_ext, Arena *arena);

i32 main(i32 argc, char **argv)
{
  Arena arena = arena_create(MiB(16));
  // arena_get_scratch(NULL);

  if (argc < 3)
  {
    printf("usage: shadertoh shaders_dir header_file [-x extension]\n");
    return 0;
  }

  String file_extension = str(".glsl");
  {
    if (argc == 5)
    {
      String option = str_from_cstr(argv[3], &arena);
      if (str_equals(option, str("-x")))
      {
        file_extension = str_from_cstr(argv[4], &arena);
      }
    }
  }

  String input_path = str_from_cstr(argv[1], &arena);
  String output_path = str_from_cstr(argv[2], &arena);

  // String input_path = str_nullify(str("..\\input\\"), &arena);
  // String output_path = str_nullify(str("..\\output\\shaders.h"), &arena);

  // Clear output
  FILE *output_file = fopen(output_path.str, "wb");
  assert(output_file);
  fputs("", output_file);
  fputs("#pragma once\n\n", output_file);

  StringArray file_names = file_names_from_dir(input_path, file_extension, &arena);
  for (i32 i = 0; i < file_names.count; i++)
  {
    String file_name = file_names.e[i];
    print_str(file_name, TRUE);
    String file_path = str_concat(input_path, file_name, &arena);
    FILE *input_file = fopen(file_path.str, "rb");
    assert(input_file);

    String lines[MAX_LINES] = {0};
    read_file_into_array(input_file, lines, &arena);
    output_file = freopen(output_path.str, "ab", output_file);

    u16 line_idx = 0;

    // Vertex shader
    String shader_var = gen_var_name(file_name, str("_VERT_SRC = \""), &arena);
    fwrite(shader_var.str, 1, shader_var.len, output_file);

    for (; !str_contains(lines[line_idx], str("@Fragment")) && lines[line_idx].str; line_idx++)
    {
      if (str_contains(lines[line_idx], str("@Vertex"))) continue;

      fwrite(lines[line_idx].str, 1, lines[line_idx].len, output_file);
      fputs(" ", output_file);
    }

    fputs("\";\n", output_file);

    // Fragment shader
    shader_var = gen_var_name(file_name, str("_FRAG_SRC = \""), &arena);
    fwrite(shader_var.str, 1, shader_var.len, output_file);

    for (; lines[line_idx].str != NULL; line_idx++)
    {
      if (str_contains(lines[line_idx], str("@Fragment"))) continue;

      fwrite(lines[line_idx].str, 1, lines[line_idx].len, output_file);
      fputs(" ", output_file);
    }

    fputs("\";\n", output_file);
  }

  arena_clear(&arena);

  return 0;
}

static
void read_file_into_array(FILE *file, String container[], Arena *arena)
{
  Arena scratch = arena_get_scratch(arena);
  String buf = str_create(BUF_SIZE, &scratch);

  for (i32 i = 0; fgets(buf.str, BUF_SIZE, file) != NULL;)
  {
    buf.len = cstr_len(buf.str) - 1;
    String line = str_copy(buf, &scratch);

    if (str_equals(line, str("\n"))) continue;
    
    container[i] = str_copy(line, arena);
    container[i] = str_strip_back(container[i], str("\n"));

    i32 comment_pos = str_find(container[i], str("//"), 0, BUF_SIZE);
    if (comment_pos != -1 && !str_contains(container[i], str("// @")))
    {
      container[i] = str_substr(container[i], 0, comment_pos);
    }

    i++;
  }

  arena_clear(&scratch);
}

static
String gen_var_name(String file_name, String suffix, Arena *arena)
{
  i32 delimiter_pos = str_find_char(file_name, '.', 0, 999);
  String name = str_substr(file_name, 0, delimiter_pos);
  name = str_to_upper(name, arena);
  String shader_var = str("const char *");
  shader_var = str_concat(shader_var, name, arena);
  shader_var = str_concat(shader_var, suffix, arena);

  return shader_var;
}

static
StringArray file_names_from_dir(String dir_name, String file_ext, Arena *arena)
{
  StringArray result;
  #if defined(_WIN32)
  result = _file_names_from_dir_windows(dir_name, file_ext, arena);
  #else
  result = _file_names_from_dir_unix(dir_name, file_ext, arena);
  #endif

  return result;
}

#if defined(__APPLE__) || defined(__linux__)
static
StringArray _file_names_from_dir_unix(String dir_name, String file_ext, Arena *arena)
{
  Arena scratch = arena_get_scratch(arena);
  StringArray result = create_str_array(MAX_FILES, arena);
  DIR *dir = opendir(dir_name.str);
  assert(dir);

  i32 count = 0;
  for (DIRENT *dirent; (dirent = readdir(dir));)
  {
    String file_name = str_copy((String) {dirent->d_name, dirent->d_namlen}, arena);
    if (!str_contains(file_name, file_ext)) continue;
    result.e[count] = file_name;
    count += 1;
  }

  result.count = count;

  arena_clear(&scratch);
  closedir(dir);

  return result;
}
#endif

#if defined(_WIN32)
static
StringArray _file_names_from_dir_windows(String dir_name, String file_ext, Arena *arena)
{
  Arena scratch = arena_get_scratch(arena);
  StringArray result = create_str_array(MAX_FILES, arena);  
  String name_pattern = str_concat(str("*"), file_ext, arena);
  String path = str_concat(dir_name, name_pattern, arena);

  WIN32_FIND_DATA finder_data;
  HANDLE finder = FindFirstFileA(path.str, &finder_data);
  i32 file_count = 0;
  if (finder != INVALID_HANDLE_VALUE)
  {
    do 
    {
      result.e[file_count] = str_from_cstr(finder_data.cFileName, arena);
      file_count++;
    }
    while (FindNextFileA(finder, &finder_data));
  }

  FindClose(finder);

  result.count = file_count;
  
  return result;
}
#endif
