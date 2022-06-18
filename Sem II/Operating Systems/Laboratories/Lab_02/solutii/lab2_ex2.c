#include <stdio.h>
#include <stdlib.h>

#define MAX 11


int main(int argc, char* argv[])
{
    // citim N
    printf("N: ");
    int N = 0;
    scanf("%d", &N);
    
    // citim cuvintele
    char cuvinte[10][N][MAX];
    for (int i = 0; i < N; i++)
    {
        printf("Cuvant[%d]: ");
        scanf("%s", cuvinte[i][0]);
    }
    
    // afisam cuvintele citite
    printf("Cuvinte citite:");
    for (int i = 0; i < N; i++)
    {
        printf("%s ", cuvinte[i]);
    }
    
    return 0;
}
