#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "globals.h"
#include "util.h"

void read_lines(FILE *file, String *lines, u16 count);

i32 main(void)
{
    FILE *file = fopen("data.ini", "r");
    assert(file != NULL);

    u64 line_count = 10;
    String lines[line_count];

    for (u64 i = 0; i < line_count; i++)
    {
        lines[i].data = NULL;
    }

    read_lines(file, lines, line_count);

    for (u64 i = 0; i < line_count; i++)
    {
        if (lines[i].data == NULL) break;

        printf("%s\n", lines[i].data);
    }

    fclose(file);

    return 0;
}

void read_lines(FILE *stream, String *data, u16 count)
{
    i8 *buffer = (i8*) malloc(BUFFER_SIZE);
    u64 i = 0;

    while (fgets(buffer, BUFFER_SIZE, stream) != NULL)
    {
        if (i == count) break;

        data[i].data = (i8*) malloc(BUFFER_SIZE);
        str_copy_buffer(&data[i], buffer);
        str_strip(&data[i], "\n");
        i++;
    }

    free(buffer);
}
