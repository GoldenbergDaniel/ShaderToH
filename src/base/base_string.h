#pragma once

#include "base_common.h"
#include "base_arena.h"

typedef struct String String;
typedef struct StringNode StringNode;
typedef struct StringArray StringArray;
typedef struct StringStack StringStack;
typedef struct StringQueue StringQueue;

// @String =====================================================================================

struct String
{
  char *str;
  u32 len;
};

#define str(s) ((String) {s, sizeof (s) - 1})

String str_create(u32 len, Arena *arena);
String str_from_cstr(char *cstr, Arena *arena);
bool str_equals(String s1, String s2);
bool str_contains(String s, String substr);
i64 str_find(String s, String substr, u64 start, u64 end);
i64 str_find_char(String s, char c, u32 start, u64 end);
String str_substr(String s, u32 start, u32 end);
String str_copy(String s, Arena *arena);
String str_copy_into(String src, String *dest);
String str_insert_at(String s, String substr, u32 loc, Arena *arena);
String str_concat(String s1, String s2, Arena *arena);
String str_strip_front(String s, String substr);
String str_strip_back(String s, String substr);
String str_nullify(String s, Arena *arena);
String str_to_lower(String s, Arena *arena);
String str_to_upper(String s, Arena *arena);
String str_join(StringArray arr, String delimiter, Arena *arena);
StringArray str_split(String s, String delimiter, Arena *arena);
void print_str(String s, bool nl);

// @StringArray ================================================================================

struct StringArray
{
  String *e;
  u64 count;
  u64 capacity;
};

StringArray create_str_array(u64 count, Arena *arena);
void clear_str_array(StringArray *arr, Arena *arena);

// @CStr =======================================================================================

u32 cstr_len(char *cstr);
void cstr_copy(String *dest, char *src);
