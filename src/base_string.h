#pragma once

#include "base_common.h"
#include "base_arena.h"

typedef struct String String;
struct String
{
  i8 *str;
  u32 len;
};

// @String =====================================================================================

String str_lit(i8 *s);
String str_alloc(u32 len, Arena *arena);
String str_copy(String src, Arena *arena);
String str_copy_into(String *dest, String src);
String str_strip_end(String s, String substr, Arena *arena);
String str_concat(String s1, String s2, Arena *arena);
String str_substr(String s, u32 start, u32 end, Arena *arena);
String str_nullify(String s, Arena *arena);
bool str_equals(String s1, String s2);
bool str_contains(String s, String substr);
i64 str_find(String s, String substr);
i64 str_find_char(String s, i8 c);
void str_print(String s);

// @CString ====================================================================================

u32 cstr_len(i8 *cstr);
void cstr_copy(String *dest, i8 *src);
