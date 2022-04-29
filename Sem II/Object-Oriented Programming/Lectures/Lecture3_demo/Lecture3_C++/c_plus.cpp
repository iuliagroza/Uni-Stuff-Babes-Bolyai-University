#include <iostream>
#include <Windows.h>

using namespace std;

auto fct(int a)
{
	return (a % 2 == 0);
}

namespace A
{
	int a = 3;
	int d = 25;

	int increaseValue(int x)
	{
		return ++x;
	}
}

namespace B
{
	int a = 5;
}

int main()
{
	system("color f4");

	// Reading and writing data
	int q = 0;
	cout << "Input a value for q: ";
	cin >> q;
	cout << "The variable q is now: " << q << "\n.";

	// ------------------------------------------------------------------------------------------------------------------------
	// References
	int x = 2;
	int& y = x; // x and y refer to the same memory location, y is an alias for x
	y = 10;
	x = 5;
	cout << "Value of x: " << x << ", value of y: " << y << ".\n";

	int* px = &x;
	int* py = &y;
	cout << "Address of x: " << px << ", address of y: " << py << ".\n"; // the memory addresses of x and y are identical.

	//int& z;		// Error - a reference must be initialized.

	// Const references
	const int& z = x;
	cout << "Value of z: " << z;
	//z = 20; // a const reference cannot be modified
	
	// ------------------------------------------------------------------------------------------------------------------------
	// auto specifier
	double m{ 2 };
	int n{ 3 };
	auto s = m + n;
	cout << "s: " << s << "\n";
	
	auto resFct = fct(20);
	auto res = resFct ? "true" : "false";
	cout << "res: " << res << "\n";

	// ------------------------------------------------------------------------------------------------------------------------
	// Namespaces
	int a = 100;
	A::a = 20;
	cout << "a in main: " << a << ", a in namespace A: " << A::a << ", a in namespace B: " << B::a << "\n";
	auto res2 = A::increaseValue(A::a);
	res2 = A::increaseValue(B::a);
	res2 = A::increaseValue(a);

	{
		using namespace A;
		cout << d << endl;  // no need to use the scope resolution operator
	}

	// ------------------------------------------------------------------------------------------------------------------------
	// Ranged-based for loop
	int v[] = { 1, 2, 3, 4, 5 };
	for (int val : v)
		cout << val << " ";
	cout << endl;

	int i{ 0 };
	for (auto val : v)	// val is a copy of each element from v (one at a time)
	{
		cout << val << " ";
		val += 100;
		cout << val << " ";
		cout << v[i] << endl;
		i++;
	}
	cout << endl;

	i = 0;
	for (auto& val : v)	// val is now a reference of each element from v => the elements will be modified
	{
		cout << val << " ";
		val += 100;
		cout << val << " ";
		cout << v[i] << endl;
		i++;
	}
	cout << endl;

	i = 0;
	for (const auto& val : v)	// val is now a const reference of each element from v => no copies are made and the elements CANNOT be modified
	{
		cout << val << " ";
		//val += 100;	// ERROR
		cout << v[i] << endl;
		i++;
	}
	cout << endl;

	return 0;
}