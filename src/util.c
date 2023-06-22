#include "string.h"

#include "globals.h"
#include "util.h"

void str_set_len(String *str)
{
    i32 len = 0;
    i32 i = 0;
    while (str->data[i] != '\0')
    {
        len++;
        i++;
    }

    str->len = len;
}

void str_copy(String *src, String *dest)
{
    dest->len = src->len;

    for (i32 i = 0; i < src->len; i++)
    {
        dest->data[i] = src->data[i];
    }

    dest->data[dest->len] = '\0';
}

void str_copy_i8ptr(i8 *src, String *dest)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest->data[i] = src[i];
        i++;
    }

    dest->data[i] = '\0';
    dest->len = i;
}

void str_strip(String *str, i8 *c)
{
    str->data[strcspn(str->data, c)] = 0;
}

i32 str_find_char(String *str, u8 c)
{
    for (i32 i = 0; i < str->len; i++)
    {
        if (str->data[i] == c) return i;
    }

    return -1;
}
