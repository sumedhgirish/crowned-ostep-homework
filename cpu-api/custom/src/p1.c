#include "common.h"

int main(int argc, const char *argv[])
{
    int x = 1000;
    printf("Hello, I am program %d, and I have set x to %d.\n", getpid(), x);

    int rd = fork();
    if (rd < 0) {
        fprintf(stderr, "Could not fork current process.\n");
        return rd;
    } else if (rd == 0) {
        x += 3;
        printf("Hello, I am the child process! I will add 3 to x. So x=%d\n", x);
        printf("Waiting for no reason.\n");
        int rch = wait(NULL);
        printf("Got %d from waiting, lmao.\n", rch);
        return 0;
    } else {
        printf("I just spawned a child process with pid:%d.\n", rd);
        int rc = wait(NULL);
        assert(rc >= 0);
        x += 5;
        printf("I, the parent will now add 5 to x, so x=%d.\n", x);
        return 0;
    }
}
