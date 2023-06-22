#pragma once

typedef struct String
{
    i8 *data;
    u32 len;
} String;

// String *str_alloc(u32 len);
void str_set_len(String *str);
i32 str_find_char(String *str, u8 c);
void str_copy(String *src, String *dest);
// void str_free(String *str);
