#pragma once

#include "base_common.h"
#include "base_arena.h"

typedef struct String String;
struct String
{
  i8 *str;
  u32 len;
};

// @String ==================================================================================

#define STR_NULL ((String) {"\0", 1})

// Returns a string with length calculated automatically.
String str_lit(i8 *s);
// Copies source string to destination string
String *str_copy(String *dest, String src);
// Appends source string to destination string
String str_concat(String s1, String s2, Arena *arena);
// Removes the last occurence of character from string. 
bool str_strip(String *s, i8 c);
// Returns whether the chracters of string1 match those of string2. 
bool str_equals(String s1, String s2);
// Returns the index of the first character in string. 
i64 str_find_char(String s, i8 c);
// TODO: Figure out what this should do
String str_substr(String s, u32 start, u32 end, Arena *arena);
// Returns the index of the first insatnce of substring in string. 
i64 str_find(String s, String substr);
// Check if string contains substring
bool str_contains(String s, String substr);
// Print string to terminal
void str_print(String str);

// @CStr ====================================================================================

// Returns the length of a c-string
u32 cstr_len(i8 *cstr);
// Copies src c-string to destination string
void cstr_copy(String *dest, i8 *src);
