#include <stdio.h>
#include <stdlib.h>

int main() {
	int n;
	printf("Enter n:");
	scanf("%d", &n);

	int *p;

	p = malloc(sizeof(int)*n);
	*p = 10;
	free(p);
	return 0;
}
