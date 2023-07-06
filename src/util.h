#pragma once

typedef struct String
{
    i8 *data;
    u32 len;
} String;

#define STR_NL (String) {"\n", 2}
#define STR_SPACE (String) {" ", 2}

// Copies String src to String destination
void str_copy(String *dest, String src);
// Copies char* src to String destination
void str_copy_cstr(String *dest, i8 *src);
// Strips char c from String str
void str_strip(String *str, i8 *c);
// Returns true if String str1 is equal to String str2. Otherwise returns false
bool str_equals(String str1, String str2);
// Returns the index of the first char in the string. Returns -1 if the char doesn't exist
i32 str_find_char(String *str, u8 c);

// Returns the length of a char*
u32 cstr_len(i8 *cstr);
