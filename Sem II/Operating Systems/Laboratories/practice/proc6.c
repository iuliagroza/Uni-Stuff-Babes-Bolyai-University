#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int p2c[2], c2p[2];
    pipe(p2c);
    pipe(c2p);
    int f = fork();
    if(f < 0) {
        perror("Unable to create child.");
        exit(1);
    } else if(f == 0) {
        close(p2c[1]);
        close(c2p[0]);
        int n, nr, rez = 0;
        if(read(p2c[0], &n, sizeof(int)) < 0) {
            perror("Error reading n.");
            close(p2c[0]);
            close(c2p[1]);
            exit(2);
        }
        for(int i=0; i<n; i++) {
            if(read(p2c[0], &nr, sizeof(int)) < 0) {
                perror("Error reading nr.");
                close(p2c[0]);
                close(c2p[1]);
                exit(3);
            }
            rez += nr;
        }
        
        rez /= n;

        if(write(c2p[1], &rez, sizeof(int)) < 0) {
            perror("Error writing rez.");
            close(p2c[0]);
            close(c2p[1]);
            exit(4);
        }
        
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
    } else {
        close(p2c[0]);
        close(c2p[1]);
    }
    return 0;
}
