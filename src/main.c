#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "util.h"

i32 main(void)
{
    FILE *file = fopen("data.txt", "r");
    u8 line_count = 4;
    String lines[line_count];

    i8 buffer[10];
    u8 i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        lines[i].data = (char*) malloc(sizeof(char)*10);
        str_copy_i8ptr(buffer, &lines[i]);
        str_strip(&lines[i], "\n");
        str_set_len(&lines[i]);
        i++;
    }

    for (u8 i = 0; i < line_count; i++)
    {
        print_str("", lines[i].data);
    }

    fclose(file);

    return 0;
}
