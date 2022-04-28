
#include <iostream>
#include "List.h"

using namespace std;

void createList(List& l) {
	l.addToBeginning(2);
	l.addToBeginning(4);
	l.addToBeginning(2);
	l.addToBeginning(5);
	l.addToBeginning(4);
}

void printList(List& l) {
	cout << "Original list:\n";
	ListIterator it = l.iterator();
	while (it.valid()) {
		cout << it.getCurrent() << ' ';
		it.next();
	}

	TElem x;
	it.first();
	while (it.valid()) {
		x= it.getCurrent()*2;
		l.setElement(it, x );
		it.next();
	}

	cout << "\nModified list:\n";
	it.first();
	while (it.valid()) {
		cout << it.getCurrent() << ' ';
		it.next();
	}
}

int main() {
	List myList;
	createList(myList);
	printList(myList);
	return 0;

}
