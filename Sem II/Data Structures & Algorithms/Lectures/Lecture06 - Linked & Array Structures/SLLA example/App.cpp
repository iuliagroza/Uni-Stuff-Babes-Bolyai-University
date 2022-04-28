
#include "Iterator.h"
#include <iostream>
#include "SLLArr.h"

using namespace std;

void createSLLA(SLLA& l) {
	l.insertFirst(2);
	l.insertFirst(4);
	l.insertFirst(2);
	l.insertFirst(5);
	l.insertFirst(4);
}

void printSLLA(const SLLA& l) {
	Iterator it = l.iterator();
	while (it.valid()) {
		cout << it.getCurrent() << ' ';
		it.next();
	}
}

int main() {
	SLLA l;
    createSLLA(l);
	printSLLA(l);
	return 0;
}
