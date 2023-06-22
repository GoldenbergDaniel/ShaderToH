#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "util.h"

i32 main(void)
{
    FILE *file = fopen("data.txt", "r");
    const u8 line_count = 4;
    String lines[line_count];

    i8 buffer[10];
    u8 i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        lines[i].data = (char*) malloc(sizeof(char)*10);
        strcpy(lines[i].data, buffer);
        i++;
    }

    for (u8 i = 0; i < line_count; i++)
    {
        print_str("", lines[i].data);
    }

    fclose(file);

    return 0;
}
