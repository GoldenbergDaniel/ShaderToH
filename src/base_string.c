#include <stdio.h>

#include "base_common.h"
#include "base_arena.h"
#include "base_string.h"

// @String =====================================================================================

inline
String str_lit(i8 *s)
{
  return (String) {s, cstr_len(s)-1};
}

String str_alloc(u32 len, Arena *arena)
{
  String result;
  result.len = len;
  result.str = arena_alloc(arena, len);

  return result;
}

String str_copy_into(String *dest, String src)
{
  for (u32 i = 0; i < src.len; i++)
  {
    dest->str[i] = src.str[i];
  }
  
  dest->len = src.len;

  return *dest;
}

String str_copy(String src, Arena *arena)
{
  String dest = {0};
  dest.str = arena_alloc(arena, src.len);
  dest.len = src.len;

  for (u32 i = 0; i < src.len; i++)
  {
    dest.str[i] = src.str[i];
  }
  
  dest.len = src.len;

  return dest;
}

String str_strip_end(String s, String substr, Arena *arena)
{
  String result = s;
  Arena scratch = arena_get_scratch(arena);

  u32 end_len = s.len - substr.len;
  String end = str_substr(s, end_len, s.len, &scratch);
  if (str_equals(end, substr))
  {
    result = str_substr(s, 0, end_len, arena);
    result.len = end_len;
  }

  arena_clear(&scratch);
  
  return result;
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

String str_concat(String s1, String s2, Arena *arena)
{
  String result = str_alloc(s1.len + s2.len, arena);

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

String str_substr(String s, u32 start, u32 end, Arena *arena)
{
  ASSERT(start >= 0 && start < s.len && end > 0 && end <= s.len && start < end);

  String result = str_alloc(end-start, arena);

  u32 result_idx = 0;
  for (u32 i = start; i < end; i++)
  {
    result.str[result_idx] = s.str[i];
    result_idx++;
  }

  return result;
}

String str_nullify(String s, Arena *arena)
{
  String result = str_alloc(s.len, arena);

  for (u32 i = 0; i < result.len; i++)
  {
    result.str[i] = s.str[i];
  }

  result.str[result.len] = '\0';

  return result;
}

bool str_contains(String s, String substr)
{
  if (s.len < substr.len) return FALSE;

  bool result = FALSE;

  for (u32 i = 0; i < s.len-substr.len+1; i++)
  {
    if (s.str[i] == substr.str[0])
    {
      for (u32 j = 0; j < substr.len; j++)
      {
        if (s.str[i+j] != substr.str[j]) break;

        if (j == substr.len-1)
        {
          result = TRUE;
          goto exit;
        }
      }
    }
  }

  exit:
  return result;
}

i64 str_find(String s, String substr)
{
  if (s.len < substr.len) return -1;

  i64 loc = -1;

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

i64 str_find_char(String s, i8 c)
{
  i64 loc = -1;

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

void str_print(String s)
{
  for (u32 i = 0; i < s.len; i++)
  {
    printf("%c", s.str[i]);
  }

  printf("\n");
}

// @CString ====================================================================================

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
