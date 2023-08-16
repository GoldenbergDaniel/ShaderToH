#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "globals.h"
#include "string.h"

String str_new(i8 *str, u32 len)
{
  String new_str;
  new_str.len = len;
  new_str.data = (i8 *) malloc(len);
  
  if (str != NULL) new_str.data = str;

  return new_str;
}

void str_free(String *str)
{
  free(str->data);
}

void str_copy(String *dest, String *src)
{
  for (u32 i = 0; i < src->len; i++)
  {
    dest->data[i] = src->data[i];
  }
  
  dest->len = src->len;
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
  for (u32 i = 0; i <= str.len - substr.len; i++)
  {
    if (str.data[i] == substr.data[0])
    {
      for (u32 j = 1; j < substr.len; j++)
      {
        if (str.data[i+j] == substr.data[j])
        {
          if (j == substr.len-1) return i;
        }

        break;
      }
    }
  }

  return -1;
}

// NOTE: Works but not good!
String str_substring(String str, u32 start, u32 end)
{
  assert(start >= 0 && start < str.len && end > 0 && end <= str.len && start < end);

  String temp = str_new(NULL, str.len);
  // String substr;

  for (u32 i = start; i < end; i++)
  {
    // temp.data[i] = str.data[i];
    break;
  }

  // log_int("i: ", i);

  memcpy(temp.data, &str.data[start], end-start);

  // str_free(&temp);

  return temp;
}

u32 cstr_len(i8 *cstr)
{
  u32 i = 0;
  while (cstr[i] != '\0')
  {
    i++;
  }

  return i+1;
}
