#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX 35

void primes(int *pipefd) {
    int first;
    if (read(pipefd[0], &first, 1)) {
        printf("prime %d\n", first);

        int new_pipefd[2];
        pipe(new_pipefd);
        int next;
        while (read(pipefd[0], &next, 1)) {
            if (next % first != 0) {
                write(new_pipefd[1], &next, 1);
            }

        }
        close(new_pipefd[1]);
        primes(new_pipefd);
    } else {
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    int pipefd[2];
    pipe(pipefd);

    for (int i = 2; i <= MAX; i++) {
        write(pipefd[1], &i, 1);
    }

    close(pipefd[1]);
    primes(pipefd);
    exit(0);
}
