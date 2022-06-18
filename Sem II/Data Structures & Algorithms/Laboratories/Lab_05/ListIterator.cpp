#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
    this->currentPosition = 0;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
void ListIterator::first(){
	//TODO - Implementation
    this->currentPosition = 0;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
void ListIterator::next(){
	//TODO - Implementation
    if (!this->valid()) {
        throw exception();
    }

    this->currentPosition++;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
bool ListIterator::valid() const{
	//TODO - Implementation
    return (this->currentPosition < list.size());
}


//BC: Theta(1)
//WC: O(H), where H is the height of the BST
//Total: O(H)
TComp ListIterator::getCurrent() const{
	//TODO - Implementation
    if (!this->valid()) {
        throw exception();
    }
    return list.getElement(this->currentPosition);
}


