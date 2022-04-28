#include "DynamicArray.h"
#include <iostream>

using namespace std;

void create(DynamicArray& v) {
	v.addToEnd(1);
	v.addToEnd(2);
	v.addToEnd(3);
	v.addToEnd(4);
}

void print1(DynamicArray& v) {

	Iterator i = v.iterator();
	while (i.valid()) {
		cout << i.getCurrent() << ' ';
		i.next();
	}
}

void print2(const DynamicArray& v) {

	// print by using indexed access
	// we should know it is 0-based

	cout << endl;
	for (int i = 0; i < v.size(); i++)
		cout << v.getElement(i) << ' ';
}

int main(void) {
	DynamicArray v(2);
	create(v);
	print1(v);
	print2(v);
	return 0;
}
