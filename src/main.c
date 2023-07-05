#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "globals.h"
#include "util.h"

void read_lines(FILE *file, String *lines, u32 count);
u32 remove_whitespace(String *lines, u32 count);

i32 main(void)
{
    FILE *file = fopen("data.ini", "r");
    assert(file != NULL);

    u32 line_count = 10;
    String lines[line_count];

    for (u32 i = 0; i < line_count; i++)
    {
        lines[i].data = NULL;
        lines[i].len = 0;
    }

    read_lines(file, lines, line_count);

    u32 wsc = remove_whitespace(lines, line_count);
    log_uint("Count: ", wsc);

    fclose(file);

    return 0;
}

void read_lines(FILE *stream, String *container, u32 count)
{
    i8 *buffer = (i8*) malloc(BUFFER_SIZE);
    u32 i = 0;

    while (fgets(buffer, BUFFER_SIZE, stream) != NULL)
    {
        if (i == count) break;

        container[i].data = (i8*) malloc(len_cstr(buffer));
        str_copy_cstr(&container[i], buffer);
        // str_strip(&container[i], "\n");
        // printf("%s\n", container[i].data);

        i++;
    }

    free(buffer);
}

// TERRIBLE CODE    
u32 remove_whitespace(String *lines, u32 count)
{
    u32 removed = 0;

    for (u32 i = 0; i < count; i++)
    {   
        if (lines[i].data == NULL) break;

        printf("%s", lines[i].data);

        if (lines[i].len == 1)
        {
            removed++;
        }
    }

    return removed;
}
