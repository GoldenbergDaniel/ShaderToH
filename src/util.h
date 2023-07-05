#pragma once

typedef struct String
{
    i8 *data;
    u32 len;
} String;

void str_copy(String *dest, String *src);
void str_copy_cstr(String *dest, i8 *src);
void str_strip(String *str, i8 *c);
i32 str_find_char(String *str, u8 c);

u32 len_cstr(i8 *cstr);
