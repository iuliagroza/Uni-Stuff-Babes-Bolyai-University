#include "ListIterator.h"
#include <iostream>

using namespace std;

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
ListIterator::ListIterator(const SortedIndexedList &list) : list(list) {
    //TODO - Implementation
    this->current = 0;
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
void ListIterator::first() {
    //TODO - Implementation
    this->current = 0;
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
void ListIterator::next() {
    //TODO - Implementation
    if (!valid()) {
        throw std::exception();
    }
    this->current++;
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
bool ListIterator::valid() const {
    //TODO - Implementation
    return this->current < this->list.size();
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
TComp ListIterator::getCurrent() const {
    //TODO - Implementation
    return this->list.getElement(current);
}


