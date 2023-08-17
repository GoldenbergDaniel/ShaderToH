#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "globals.h"
#include "string.h"

// Copies source C-string to destination string
static void cstr_copy(String *dest, i8 *src);

String str_new(i8 *str, u32 len)
{
  String new_str;
  new_str.data = (i8 *) malloc(len);
  new_str.len = len;
  
  if (str != NULL) cstr_copy(&new_str, str);

  return new_str;
}

inline
void str_free(String *str)
{
  free(str->data);
}

inline
String str_lit(i8 *str)
{
  return (String) {str, cstr_len(str)-1};
}

void str_copy(String *dest, String src)
{
  for (u32 i = 0; i < src.len; i++)
  {
    dest->data[i] = src.data[i];
  }
  
  dest->len = src.len;
}

String *str_concat(String *dest, String *src)
{
  for (u32 i = 0; i < src->len; i++)
  {
    dest->data[i+dest->len] = src->data[i];
  }

  dest->len = dest->len + src->len;

  return dest;
}

bool str_strip(String *str, i8 c)
{
  for (u32 i = str->len; i > 0; i--)
  {
    if (str->data[i-1] == c)
    {
      str->data[i-1] = 0;
      str->len--;

      return TRUE;
    }
  }
  
  return FALSE;
}

bool str_equals(String str1, String str2)
{
  if (str1.len != str2.len) return FALSE;

  for (u32 i = 0; i < str1.len; i++)
  {
    if (str1.data[i] != str2.data[i]) return FALSE;
  }

  return TRUE;
}

i32 str_find_char(String str, u8 c)
{
  for (u32 i = 0; i < str.len; i++)
  {
    if (str.data[i] == c) return i;
  }

  return -1;
}

i32 str_find_substr(String str, String substr)
{
  for (u32 i = 0; i < str.len-substr.len+1; i++)
  {
    if (str.data[i] == substr.data[0])
    {
      for (u32 j = 1; j < substr.len; j++)
      {
        if (str.data[i+j] != substr.data[j]) break;
        if (j == substr.len-1) return i;
      }
    }
  }

  return -1;
}

// String str_substring(String str, u32 start, u32 end)
// {
//   assert(start >= 0 && start < str.len && end > 0 && end <= str.len && start < end);

//   return (String) {"", 0};
// }

u32 cstr_len(i8 *cstr)
{
  u32 i = 0;
  while (cstr[i] != '\0')
  {
    i++;
  }

  return i+1;
}

static
void cstr_copy(String *dest, i8 *src)
{
  u32 src_len = cstr_len(src)-1;

  for (u32 i = 0; i < src_len; i++)
  {
    dest->data[i] = src[i];
  }
  
  dest->len = src_len;
}
