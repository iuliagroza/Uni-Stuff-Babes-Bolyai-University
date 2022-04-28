#include "List.h"
#include <exception>
using namespace std;

struct List::SLLNode	{
		TElem info;
		PNode next;
		SLLNode(TElem e, PNode n);
};

List::SLLNode::SLLNode(TElem e, PNode n) {
	info = e;
	next = n;
}


List::List() {
	head = nullptr;
}

void List::addToBeginning(TElem e) {
	PNode pn = new SLLNode(e, nullptr);
	pn->next = head;
	head = pn;
}

// changes the element from the current position to the given one.
//returns the old value from the position
//throws exception if the position is not valid
TElem List::setElement(ListIterator pos, TElem e){
	PNode pn;
	pn = pos.currentElement;
	if (pn == nullptr){
		throw exception();
	} else {
		TElem old;
		old = pn->info;
		pn->info = e;
		return old;
	}

}

ListIterator List::iterator() const {
	return ListIterator(*this);
}

List::~List() {
	while (head != nullptr) {
		PNode p = head;
		head = head->next;
		delete p;
	}
}

ListIterator::ListIterator(const List& l) : list(l) {
	currentElement = l.head;
}

void ListIterator::first() {
	currentElement = list.head;
}

void ListIterator::next() {
	if ( currentElement == nullptr) throw exception();
	currentElement = currentElement->next;
}

bool ListIterator::valid() const {
	return currentElement != nullptr;
}

TElem ListIterator::getCurrent() const {
	if ( currentElement == nullptr) throw exception();
	return currentElement->info;
}
