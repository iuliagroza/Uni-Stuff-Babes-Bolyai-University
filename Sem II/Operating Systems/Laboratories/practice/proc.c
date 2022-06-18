#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void f(int n) {
    if(n > 0) {
        if(fork() == 0) {
            printf("PID: %d, PPID: %d\n", getpid(), getppid());
            f(n-1);
        }
        wait(0);
    }
    exit(0);
}    

int main() {
    f(3);
    return 0;
}
