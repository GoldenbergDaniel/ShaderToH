#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "util.h"

void read_lines(FILE *file, String *lines, u16 size);

i32 main(void)
{
    FILE *file = fopen("data.txt", "r");
    u64 line_count = 588;
    String lines[line_count];

    read_lines(file, lines, 10);

    for (u64 i = 0; i < line_count; i++)
    {
        print_str("", lines[i].data);
    }

    fclose(file);

    return 0;
}

void read_lines(FILE *file, String *data, u16 size)
{
    i8 *buffer = (i8*) malloc(sizeof(i8) * size);
    u64 i = 0;

    while (fgets((i8*) buffer, sizeof(buffer), file) != NULL)
    {
        data[i].data = (i8*) malloc(sizeof(i8) * 10);
        str_copy_buffer(&data[i], buffer);
        str_strip(&data[i], "\n");
        str_set_len(&data[i]);
        i++;
    }

    free(buffer);
}
