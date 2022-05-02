#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void r(int s) {
	printf("Not yet!\n");
}

int main() {
	signal(SIGHUP, r);
	printf("Process A pid: %d \n", getpid());
	int n;
	scanf("%d", &n);
	return 0;
}
