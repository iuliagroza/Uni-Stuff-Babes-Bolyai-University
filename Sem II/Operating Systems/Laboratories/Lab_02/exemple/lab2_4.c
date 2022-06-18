#include <stdio.h>

int main(int argc, char *argv[])
{
	long t[10], *p;

	int i;
	for (i=0; i<10; t[i++]=i);

	p = t;

	for (i=0; i<10; i++)
		printf("%d %d %d %d\n", t[i], p[i], *(p+1), *(t+1));

	return 0;
}
