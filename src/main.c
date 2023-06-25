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
        lines[i].len = 0;
    }

    read_lines(file, lines, line_count);

    fclose(file);

    return 0;
}

void read_lines(FILE *stream, String *container, u16 count)
{
    i8 *buffer = (i8 *) malloc(BUFFER_SIZE);
    u64 i = 0;

    while (fgets(buffer, BUFFER_SIZE, stream) != NULL)
    {
        if (i == count) break;

        container[i].data = (i8*) malloc(buffer_len(buffer));
        str_copy_buffer(&container[i], buffer);
        str_strip(&container[i], "\n");
        printf("%s\n", container[i].data);

        i++;
    }

    free(buffer);
}
