#pragma once

#include "base_common.h"
#include "base_memory.h"

typedef struct String String;
struct String
{
  i8 *str;
  u32 len;
};

// Returns a string with length calculated automatically.
String str_lit(i8 *str);
// Copies source string to destination string
String *str_copy(String *dest, String src);
// Appends source string to destination string
String str_concat(String str1, String str2, Arena *arena);
// Removes the last occurence of character from string. 
// Returns false if doesn't exist
b8 str_strip(String *str, i8 c);
// Returns whether the chracters of string1 match those of string2. 
b8 str_equals(String str1, String str2);
// Returns the index of the first character in string. 
// Returns -1 if char doesn't exist.
i32 str_find_char(String str, i8 c);
// Returns the index of the first insatnce of substring in string. 
// Returns -1 if substring doesn't exist.
i32 str_find_substr(String str, String substr);
// NOTE: Broken! Should return a pointer to the substring??
String str_substring(String str, u32 start, u32 end);

void str_print(String str);

// Returns the length of a C-string
u32 cstr_len(i8 *cstr);
