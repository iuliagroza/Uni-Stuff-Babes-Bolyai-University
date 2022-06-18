#include <stdio.h>

typedef struct
{
	double arr[10];
	int length;
} vector;

typedef double (*operation)(double, double);

double operationOnVector(vector v, operation o)
{
	if (v.length == 0)
		return 0;
	double result = v.arr[0];
	for (int i = 1; i < v.length; i++)
		result = o(result, v.arr[i]);		// call the function through a pointer
	return result;
}

double sum(double a, double b)
{
	return a + b;
}

double product(double a, double b)
{
	return a * b;
}

vector readNumbers()
{
	vector res;
	res.length = 0;

	printf("Enter several numbers. When entering '0', the reading will stop.\n");

	double n = -1;
	while (n != 0)
	{
		printf("Enter number: ");
		scanf("%lf", &n);
		if (n != 0)
			res.arr[res.length++] = n;
	}
	return res;
}

int pointerToFunction()
{
	// read vector
	vector v = readNumbers();

	// read operation
	char op = '+'; // by default, we compute the sum
	printf("Input '+' for addition, or '*' for multiplication: ");
	scanf(" %c", &op);

	operation o = NULL;
	if (op == '+')
		o = &sum;
	else
		o = &product;
	//operation o = (op == '+') ? &sum : &product;

	double p = operationOnVector(v, o);
	printf("The result is: %.2lf.\n", p);

	return 0;
}

//int main() {
//	pointerToFunction();
//	return 0;
//}