#pragma once

typedef struct String
{
    i8 *data;
    u32 len;
} String;

void str_set_len(String *str);
void str_copy_string(String *dest, String *src);
void str_copy_buffer(String *str, i8 *buffer);
void str_strip(String *str, i8 *c);
i32 str_find_char(String *str, u8 c);
