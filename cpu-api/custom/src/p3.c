#include "common.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
    int pipe_ends[2];
    int pd = pipe(pipe_ends);
    assert(pd == 0);

    int rd = fork();
    if (rd < 0) {
        printf("An error occured!\n");
        return rd;
    } else if (rd == 0) {
        printf("hello\n");
        write(pipe_ends[1], "d", 1);
        return 0;
    } else {
        char output;
        do {
            read(pipe_ends[0], &output, 1);
        } while(output != 'd');
        printf("goodbye\n");
    }

    return 0;
}
