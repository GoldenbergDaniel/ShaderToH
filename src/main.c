#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "globals.h"
#include "util.h"

void read_lines(FILE *stream, String *container, u32 count);

i32 main(void)
{
    FILE *file = fopen("input/test.ini", "r");
    assert(file != NULL);

    const u32 line_count = 10;
    String lines[line_count];

    read_lines(file, lines, line_count);

    fclose(file);

    return 0;
}

void read_lines(FILE *stream, String *container, u32 count)
{
    String buf; 
    buf.data = (i8*) malloc(BUFFER_SIZE);

    u32 i = 0;
    while (fgets(buf.data, BUFFER_SIZE, stream) != NULL)
    {
        if (i == count) break;

        buf.len = cstr_len(buf.data);

        if (str_equals(buf, STR_NL)) continue;

        str_strip(&buf, '\0');
        
        container[i].data = (i8*) malloc(buf.len);
        str_copy(&container[i], buf);
        str_strip(&container[i], '\n');

        printf("%s\n", container[i].data);

        i++;
    }

    free(buf.data);
}
