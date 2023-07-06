#include <stdio.h>
#include <string.h>

#include "globals.h"
#include "util.h"

void str_copy(String *dest, String src)
{
    for (u32 i = 0; i < src.len; i++)
    {
        dest->data[i] = src.data[i];
    }
    
    dest->len = src.len;
}

void str_strip(String *str, i8 *c)
{
    str->data[strcspn(str->data, c)] = 0; // wtf does this do again?
    str->len--;
}

bool str_equals(String str1, String str2)
{
    if (str1.len != str2.len) return FALSE;

    u32 longer = str1.len > str2.len ? str1.len : str2.len;
    for (u32 i = 0; i < longer; i++)
    {
        if (str1.data[i] != str2.data[i]) return FALSE;
    }

    return TRUE;
}

i32 str_find_char(String *str, u8 c)
{
    for (u32 i = 0; i < str->len; i++)
    {
        if (str->data[i] == c) return i;
    }

    return -1;
}

u32 cstr_len(i8 *cstr)
{
    u32 i = 0;
    while (cstr[i] != '\0')
    {
        i++;
    }

    return i+1;
}
