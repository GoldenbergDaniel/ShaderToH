#include <stdio.h>
#include <assert.h>

#include "base_common.h"
#include "base_arena.h"
#include "base_string.h"

// @String ===============================================================================

String str_create(u32 len, Arena *arena)
{
  String result;
  result.str = arena_alloc(arena, len);
  result.len = len;

  return result;
}

inline
String str_from_cstr(char *cstr, Arena *arena)
{
  return str_copy((String) {cstr, cstr_len(cstr)-1}, arena);
}

bool str_equals(String s1, String s2)
{
  if (s1.len != s2.len) return FALSE;

  bool result = TRUE;

  for (u32 i = 0; i < s1.len; i++)
  {
    if (s1.str[i] != s2.str[i])
    {
      result = FALSE;
      break;
    }
  }

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
          return result;
        }
      }
    }
  }

  return result;
}

i64 str_find(String s, String substr, u64 start, u64 end)
{
  if (s.len < substr.len || start >= s.len) return -1;

  i64 result = -1;

  for (u32 i = start; i < s.len-substr.len+1; i++)
  {
    if (s.str[i] == substr.str[0])
    {
      for (u32 j = 0; j < substr.len; j++)
      {
        if (s.str[i+j] != substr.str[j]) break;

        if (j == substr.len-1)
        {
          result = i;
          return result;
        }
      }
    }
  }

  return result;
}

i64 str_find_char(String s, char c, u32 start, u64 end)
{
  if (start >= s.len) return FALSE;

  i64 result = -1;

  for (u32 i = start; i < s.len; i++)
  {
    if (s.str[i] == c)
    {
      result = i;
      break;
    }
  }

  return result;
}

String str_copy(String s, Arena *arena)
{
  String result = {0};
  result.str = arena_alloc(arena, s.len+1);

  for (u32 i = 0; i < s.len; i++)
  {
    result.str[i] = s.str[i];
  }
  
  result.len = s.len;
  result.str[result.len] = '\0';

  return result;
}

String str_copy_into(String src, String *dest)
{
  for (u32 i = 0; i < src.len; i++)
  {
    dest->str[i] = src.str[i];
  }
  
  dest->len = src.len;

  return *dest;
}

String str_insert_at(String s, String substr, u32 loc, Arena *arena)
{ 
  u32 len = s.len >= substr.len + loc ? s.len : substr.len + loc;
  String result = str_create(len, arena);

  u32 substr_idx = 0;
  for (u32 i = 0; i < len; i++)
  {
    if (i >= loc && i < substr.len + loc)
    {
      result.str[i] = substr.str[substr_idx];
      substr_idx++;
    }
    else
    {
      result.str[i] = s.str[i];
    }
  }

  return result;
}

String str_concat(String s1, String s2, Arena *arena)
{
  String result = str_create(s1.len + s2.len + 1, arena);
  result.len -= 1;

  for (u32 i = 0; i < s1.len; i++)
  {
    result.str[i] = s1.str[i];
  }

  for (u32 i = 0; i < s2.len; i++)
  {
    result.str[i+s1.len] = s2.str[i];
  }

  result.str[result.len] = '\0';

  return result;
}

String str_substr(String s, u32 start, u32 end)
{
  assert(start >= 0 && start < s.len && end > 0 && end <= s.len && start < end);

  String result = {0};
  result.str = s.str + start;
  result.len = end - start;

  return result;
}


String str_strip_front(String s, String substr)
{
  assert(substr.len <= s.len);

  String result = {0};

  u32 front_len = substr.len;
  String front = str_substr(s, 0, front_len);
  if (str_equals(front, substr))
  {
    result = str_substr(s, front_len, s.len);
    result.len = s.len-front_len;
  }
  
  return result;
}

String str_strip_back(String s, String substr)
{
  assert(substr.len <= s.len);

  String result = {0};

  u32 back_len = s.len - substr.len;
  String back = str_substr(s, back_len, s.len);
  if (str_equals(back, substr))
  {
    result = str_substr(s, 0, back_len);
    result.len = back_len;
  }
  
  return result;
}

String str_nullify(String s, Arena *arena)
{
  String result = str_create(s.len, arena);

  for (u32 i = 0; i < result.len; i++)
  {
    result.str[i] = s.str[i];
  }

  result.str[result.len] = '\0';

  return result;
}

String str_to_lower(String s, Arena *arena)
{
  String result = str_create(s.len, arena);

  for (size_t i = 0; i < s.len; i++)
  {
    if (s.str[i] >= 'A' && s.str[i] <= 'Z')
    {
      result.str[i] = s.str[i] + 32;
    }
    else
    {
      result.str[i] = s.str[i];
    }
  }

  return result;
}

String str_to_upper(String s, Arena *arena)
{
  String result = str_create(s.len, arena);

  for (size_t i = 0; i < s.len; i++)
  {
    if (s.str[i] >= 'a' && s.str[i] <= 'z')
    {
      result.str[i] = s.str[i] - 32;
    }
    else
    {
      result.str[i] = s.str[i];
    }
  }

  return result;
}

String str_join(StringArray arr, String delimiter, Arena *arena)
{
  String result = {0};
  String temp = {0};

  size_t total_len = (arr.count-1) * delimiter.len;
  for (size_t i = 0; i < arr.count; i++)
  {
    total_len += arr.e[i].len;
  }

  result = str_create(total_len, arena);

  Arena scratch = arena_get_scratch(arena);

  size_t start_offset = 0;
  for (size_t i = 0; i < arr.count; i++)
  {
    temp = str_insert_at(temp, arr.e[i], start_offset, &scratch);
    start_offset += arr.e[i].len;

    if (i != arr.count-1)
    {
      temp = str_insert_at(temp, delimiter, start_offset, &scratch);
      start_offset += delimiter.len;
    }
  }

  result = str_copy(temp, arena);
  
  arena_clear(&scratch);

  return result;
}

StringArray str_split(String s, String delimiter, Arena *arena)
{
  StringArray result = {0};

  return result;
}

void print_str(String s, bool nl)
{
  for (u32 i = 0; i < s.len; i++)
  {
    printf("%c", s.str[i]);
  }

  if (nl) printf("\n");
}

// @StringArray ==========================================================================

StringArray create_str_array(u64 capacity, Arena *arena)
{
  StringArray arr = {0};
  arr.capacity = capacity;
  arr.count = capacity;
  arr.e = arena_alloc(arena, sizeof (String) * capacity);

  return arr;
}

void clear_str_array(StringArray *arr, Arena *arena)
{
  for (u64 i = 0; i < arr->count; i++)
  {
    arr->e[i] = str("");
  }

  arr->count = 0;
}

// @CString ==============================================================================

inline
u32 cstr_len(char *s)
{
  u32 len = 0;
  for (; s[len]; len++);
  return len+1;
}

void copy_cstr_into_str(String *dest, char *src)
{
  u32 len = cstr_len(src)-1;
  for (u32 i = 0; i < len; i++)
  {
    dest->str[i] = src[i];
  }
  
  dest->len = len;
}
