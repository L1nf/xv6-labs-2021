#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void print(int pid, const char *s) {
    printf("%d: received %s\n", getpid(), s);
}

void pingpong() {
    int pipefd0[2], pipefd1[2];

    pipe(pipefd0);
    pipe(pipefd1);

    if (fork() == 0) {
        char s[4];
        close(pipefd0[1]);
        read(pipefd0[0], s, 4);
        print(getpid(), s);
        write(pipefd1[1], "pong", 4);
        close(pipefd1[1]);
        exit(0);
    } else {
        char s[4];
        close(pipefd1[1]);
        write(pipefd0[1], "ping", 4);
        close(pipefd0[1]);
        read(pipefd1[0], s, 4);
        print(getpid(), s);
    }
}

int main(int argc, char *argv[]) {
    pingpong();
    exit(0);
}