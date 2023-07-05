#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "util.h"

void str_copy(String *dest, String *src)
{
    for (u32 i = 0; i < src->len; i++)
    {
        dest->data[i] = src->data[i];
        printf("%c\n", dest->data[i]);
    }
    
    dest->len = src->len;
}

void str_copy_cstr(String *dest, i8 *src)
{
    u32 i = 0;
    while (src[i] != '\0')
    {
        dest->data[i] = src[i];
        i++;
    }

    dest->len = i;
}

void str_strip(String *str, i8 *c)
{
    str->data[strcspn(str->data, c)] = 0;
    str->len--;
}

i32 str_find_char(String *str, u8 c)
{
    for (u32 i = 0; i < str->len; i++)
    {
        if (str->data[i] == c) return i;
    }

    return -1;
}

u32 len_cstr(i8 *cstr)
{
    u32 i = 0;
    while (cstr[i] != '\0')
    {
        i++;
    }

    return i;
}
