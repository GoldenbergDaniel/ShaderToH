#pragma once

typedef struct String
{
    i8 *data;
    u32 len;
} String;

// String *str_alloc(u32 len);
void str_set_len(String *str);
void str_copy(String *src, String *dest);
void str_copy_i8ptr(i8 *src, String *dest);
void str_strip(String *str, i8 *c);
i32 str_find_char(String *str, u8 c);
// void str_free(String *str);
