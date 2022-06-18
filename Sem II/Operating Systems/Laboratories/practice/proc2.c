#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void f(int n) {
    if(n > 0) {
        int p = fork();
        if(p < 0) {
            perror("Unable to create child process.");
            exit(1);
        } else if(p == 0) {
            printf("PID: %d; PPID: %d\n", getpid(), getppid());
            f(n-1);
        }
        wait(0);
    }
    exit(0);
}

int main() {
    int n;
    scanf("%d", &n);
    f(3);
    return 0;
}
