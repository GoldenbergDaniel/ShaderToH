#include <stdio.h>

#include "base_common.h"
#include "base_memory.h"
#include "string.h"

static void cstr_copy(String *dest, i8 *src);

inline
String str_lit(i8 *str)
{
  return (String) {str, cstr_len(str)-1};
}

void str_copy(String *dest, String src)
{
  for (u32 i = 0; i < src.len; i++)
  {
    dest->str[i] = src.str[i];
  }
  
  dest->len = src.len;
}

String str_concat(String str1, String str2, Arena *arena)
{
  String new_str = {0};
  new_str.len = str1.len + str2.len;
  new_str.str = arena_alloc(arena, new_str.len);

  for (u32 i = 0; i < str1.len; i++)
  {
    new_str.str[i] = str1.str[i];
  }

  for (u32 i = 0; i < str2.len; i++)
  {
    new_str.str[i+str1.len] = str2.str[i];
  }

  return new_str;
}

b8 str_strip(String *str, i8 c)
{
  b8 exists = FALSE;

  for (u32 i = str->len; i > 0; i--)
  {
    if (str->str[i-1] == c)
    {
      str->str[i-1] = 0;
      str->len--;
      exists = TRUE;
      break;
    }
  }
  
  return exists;
}

b8 str_equals(String str1, String str2)
{
  if (str1.len != str2.len) return FALSE;

  b8 equals = TRUE;

  for (u32 i = 0; i < str1.len; i++)
  {
    if (str1.str[i] != str2.str[i])
    {
      equals = FALSE;
      break;
    }
  }

  return equals;
}

i32 str_find_char(String str, i8 c)
{
  i32 loc = -1;

  for (u32 i = 0; i < str.len; i++)
  {
    if (str.str[i] == c)
    {
      loc = i;
      break;
    }
  }

  return loc;
}

i32 str_find_substr(String str, String substr)
{
  i32 loc = -1;

  for (u32 i = 0; i < str.len-substr.len+1; i++)
  {
    if (str.str[i] == substr.str[0])
    {
      for (u32 j = 1; j < substr.len; j++)
      {
        if (str.str[i+j] != substr.str[j]) break;

        if (j == substr.len-1)
        {
          loc = i;
          goto end;
        }
      }
    }
  }

  end:
  return loc;
}

// String str_substring(String str, u32 start, u32 end)
// {
//   assert(start >= 0 && start < str.len && end > 0 && end <= str.len && start < end);

//   return (String) {"", 0};
// }

void str_print(String str)
{
  for (u32 i = 0; i < str.len; i++)
  {
    printf("%c", str.str[i]);
  }

  printf("\n");
}

u32 cstr_len(i8 *cstr)
{
  u32 len = 0;
  for (; cstr[len]; len++);

  return len+1;
}

static
void cstr_copy(String *dest, i8 *src)
{
  u32 len = cstr_len(src)-1;
  for (u32 i = 0; i < len; i++)
  {
    dest->str[i] = src[i];
  }
  
  dest->len = len;
}
