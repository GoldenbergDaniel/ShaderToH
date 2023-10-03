#include <stdio.h>

#include "base_common.h"
#include "base_arena.h"
#include "base_string.h"

// @String ==================================================================================

inline
String str_lit(i8 *s)
{
  return (String) {s, cstr_len(s)-1};
}

String *str_copy(String *dest, String src)
{
  for (u32 i = 0; i < src.len; i++)
  {
    dest->str[i] = src.str[i];
  }
  
  dest->len = src.len;

  return dest;
}

String str_concat(String s1, String s2, Arena *arena)
{
  String result = {0};
  result.len = s1.len + s2.len;
  result.str = arena_alloc(arena, result.len);

  for (u32 i = 0; i < s1.len; i++)
  {
    result.str[i] = s1.str[i];
  }

  for (u32 i = 0; i < s2.len; i++)
  {
    result.str[i+s1.len] = s2.str[i];
  }

  return result;
}

bool str_strip(String *s, i8 c)
{
  bool exists = FALSE;

  for (u32 i = s->len; i > 0; i--)
  {
    if (s->str[i-1] == c)
    {
      s->str[i-1] = 0;
      s->len--;
      exists = TRUE;
      break;
    }
  }
  
  return exists;
}

bool str_equals(String s1, String s2)
{
  if (s1.len != s2.len) return FALSE;

  bool equals = TRUE;

  for (u32 i = 0; i < s1.len; i++)
  {
    if (s1.str[i] != s2.str[i])
    {
      equals = FALSE;
      break;
    }
  }

  return equals;
}

i32 str_find_char(String s, i8 c)
{
  i32 loc = -1;

  for (u32 i = 0; i < s.len; i++)
  {
    if (s.str[i] == c)
    {
      loc = i;
      break;
    }
  }

  return loc;
}

String str_substr(String str, u32 start, u32 end, Arena *arena)
{
  assert(start >= 0 && start < str.len && end > 0 && end <= str.len && start < end);

  return (String) {"", 0};
}

i32 str_find(String s, String substr)
{
  if (s.len < substr.len) return FALSE;

  i32 loc = -1;

  for (u32 i = 0; i < s.len-substr.len+1; i++)
  {
    if (s.str[i] == substr.str[0])
    {
      for (u32 j = 1; j < substr.len; j++)
      {
        if (s.str[i+j] != substr.str[j]) break;

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

bool str_contains(String s, String substr)
{
  if (s.len < substr.len) return FALSE;

  bool contains = FALSE;

  for (u32 i = 0; i < s.len-substr.len+1; i++)
  {
    if (s.str[i] == substr.str[0])
    {
      for (u32 j = 1; j < substr.len; j++)
      {
        if (s.str[i+j] != substr.str[j]) break;

        if (j == substr.len-1)
        {
          contains = TRUE;
          goto end;
        }
      }
    }
  }

  end:
  return contains;
}

void str_print(String s)
{
  for (u32 i = 0; i < s.len; i++)
  {
    printf("%c", s.str[i]);
  }

  printf("\n");
}

// @CString =================================================================================

u32 cstr_len(i8 *s)
{
  u32 len = 0;
  for (; s[len]; len++);
  return len+1;
}

void cstr_copy(String *dest, i8 *src)
{
  u32 len = cstr_len(src)-1;
  for (u32 i = 0; i < len; i++)
  {
    dest->str[i] = src[i];
  }
  
  dest->len = len;
}
