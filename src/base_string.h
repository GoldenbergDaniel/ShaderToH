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

String str_lit(i8 *s);
String str_new(u32 len, Arena *arena);
String *str_copy(String *dest, String src);
bool str_equals(String s1, String s2);
bool str_strip(String *s, i8 c); // alloc new stirng; strings are immutable
String str_concat(String s1, String s2, Arena *arena);
String str_substr(String s, u32 start, u32 end, Arena *arena);
String str_nullify(String s, Arena *arena);
bool str_contains(String s, String substr);
i64 str_find(String s, String substr);
i64 str_find_char(String s, i8 c);
void str_print(String str);

// @CStr ====================================================================================

u32 cstr_len(i8 *cstr);
void cstr_copy(String *dest, i8 *src);
