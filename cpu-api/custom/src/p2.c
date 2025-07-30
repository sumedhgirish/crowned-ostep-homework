#include "common.h"
#include <string.h>
#include <fcntl.h>

void run_as_child(int fd);
void run_as_parent(int fd, int rd);


int main(int argc, const char *argv[])
{
    // Open a file
    int fd = open("p2.output", O_RDWR | O_CREAT | O_TRUNC);
    if (fd < 0) {
        fprintf(stderr, "Could not access file 'p2.output'.\n");
        return fd;
    }

    int rd = fork();
    assert(rd >= 0);

    switch (rd) {
        case 0: run_as_child(fd); break;
        default: run_as_parent(fd, rd);
    }

    return 0;
}

void run_as_parent(int fd, int rd)
{
    printf("(%d) Spawned a child process %d as parent.\n", getpid(), rd);

    const char message[20] = "Hello, File!\n";
    for (int i=0; i < 20; ++i)
        write(fd, message, strlen(message));

    wait(NULL);
    close(fd);
    return;
}


void run_as_child(int fd)
{
    printf("(%d) Child Process spawned successfully!\n", getpid());

    const char message[20] = "Child was here.\n";
    for (int i=0; i < 20; ++i)
        write(fd, message, strlen(message));

    return;
}
