#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "util.h"

void str_set_len(String *str)
{
    i32 i = 0;
    while (str->data[i] != '\0')
    {
        i++;
    }

    str->len = i+1;
}

void str_add_terminator(String *str)
{
    str->data[str->len] = '\0';
    printf("Added a null terminator to string %s\n", str->data);
}

void str_copy_string(String *dest, String *src)
{
    for (i32 i = 0; i < src->len; i++)
    {
        dest->data[i] = src->data[i];
        printf("%c\n", dest->data[i]);
    }
    
    dest->len = src->len;

    if (dest->data[dest->len] != '\0') 
    {
        str_add_terminator(dest);
    }
}

void str_copy_buffer(String *str, i8 *buf)
{
    i32 i = 0;
    while (buf[i] != '\0')
    {
        str->data[i] = buf[i];
        i++;
    }

    str->len = i;

    if (str->data[str->len] != '\0') 
    {
        str_add_terminator(str);
    }
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

u32 buffer_len(i8 *buf)
{
    i32 i = 0;
    while (buf[i] != '\0')
    {
        i++;
    }

    return i;
}

