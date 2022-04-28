#include <exception>
#include "DynamicArray.h"

using namespace std;

void DynamicArray::resize() {

	TElem *newElems = new TElem[2 * cap];
	for (int i = 0; i < nrElem; i++)
		newElems[i] = elems[i];
	cap = 2 * cap;
	delete[] elems;
	elems = newElems;
}

DynamicArray::DynamicArray(int cp) {
	this->cap = cp;
	elems = new TElem[cp];
	this->nrElem = 0;
}

DynamicArray::~DynamicArray() {
	delete[] elems;
}

int DynamicArray::size() const{
	return nrElem;
}

TElem DynamicArray::getElement(int i) const{
	if ((i >= nrElem)||(i<0)) throw exception();

	return elems[i];
}

void DynamicArray::addToEnd(TElem e) {
	if (nrElem == cap)
		resize();
	this->elems[nrElem] = e;
	nrElem++;
}

Iterator DynamicArray::iterator() {
	return Iterator(*this);
}



Iterator::Iterator(const DynamicArray& _v) : v(_v) {
	current = 0;
}

void Iterator::first() {
	current = 0;
}

bool Iterator::valid() const{
	return current < v.size();
}

TElem Iterator::getCurrent() const{
	if (current == v.size()) throw exception();
	return v.elems[current];
}


void Iterator::next() {
	if (current == v.size()) throw exception();
	current++;
}

