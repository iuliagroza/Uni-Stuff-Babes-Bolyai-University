#include <stdio.h>

int positive(int x);

int main()
{
	freopen("numbers.txt", "r", stdin);

	int X, x[10] = {-25, 100, 99, 7, -4, 99, -2, -1, -588}, n = 9, len_p = 0, len_n = 0, P[100], N[100];
	scanf("%d", &n);

	for(int i=0; i<n; i++) {
		scanf("%d", &X);
		int is_positive = positive(x[i]);
		if (is_positive) {
			P[len_p++] = x[i];
		}
		else {
			N[len_n++] = x[i];
		}
	}

	printf("P = ");
	for (int i = 0; i < len_p; i++) {
		printf("%d ", P[i]);
	}

	printf("\nN = ");
	for (int i = 0; i < len_n; i++) {
		printf("%d ", N[i]);
	}

	fclose(stdin);
}