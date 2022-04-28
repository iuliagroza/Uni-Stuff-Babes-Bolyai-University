#include "Iterator.h"
#include "SLLArr.h"

#include <exception>
using namespace std;



Iterator::Iterator(const SLLA& l) :	slla(l) {
	current = l.head;
}

void Iterator::first() {
	current = slla.head;
}

void Iterator::next() {
	if (current == -1) throw exception();
	current = slla.next[current];
}

bool Iterator::valid() const {
	return current != -1;
}

TElem Iterator::getCurrent() const {
	if (current == -1) throw exception();
	return slla.elems[current];
}
