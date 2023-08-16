#pragma once

#include "globals.h"

typedef struct String String;
struct String
{
  i8 *data;
  u32 len;
};

// Returns a new string with length len and allocates len bytes. 
// Returns empty string if NULL is passed.
String str_new(i8 *str, u32 len);
// Frees the memory of the data in string
void str_free(String *str);
// Returns a string with length calculated automatically.
String str_lit(i8 *str);
// Copies source string to destination string
void str_copy(String *dest, String *src);
// Appends source string to destination string
void str_concat(String *dest, String *src);
// Removes the last occurence of character from string. 
// Returns false if doesn't exist
bool str_strip(String *str, i8 c);
// Returns whether the chracters of string1 match those of string2. 
bool str_equals(String str1, String str2);
// Returns the index of the first character in string. 
// Returns -1 if char doesn't exist.
i32 str_find_char(String str, u8 c);
// Returns the index of the first insatnce of substring in string. 
// Returns -1 if substring doesn't exist.
i32 str_find_substr(String str, String substr);
// NOTE: Broken! Should return a pointer to the substring??
String str_substring(String str, u32 start, u32 end);

// Returns the length of a C string (char *)
u32 cstr_len(i8 *cstr);
