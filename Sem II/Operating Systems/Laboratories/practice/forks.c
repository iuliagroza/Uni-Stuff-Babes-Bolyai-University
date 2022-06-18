#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    char* s[3] = {"A", "B", "C"};
    for(int i=0; i<3; i++) {
        if(fork() != 0) {
            execl("/bin/echo", "/bin/echo", s[i], NULL);
        }
    } 
    return 0;
}
