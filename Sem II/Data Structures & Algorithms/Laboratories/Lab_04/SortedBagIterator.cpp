#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;


//BC: Theta(N^2), where N is the number of elements
//WC: Theta(N^2)
//Total: Theta(N^2)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    //TODO - Implementation
    this->copy_elems = new TComp[b.nr_elements];
    int k = 0;
    for (int i = 0; i < this->bag.m; i++) {
        struct Node* current_node = this->bag.hashtable[i];
        while (current_node != NULL) {
            for(int j=0; j<current_node->freq; j++) {
                this->copy_elems[k++] = current_node->elem;
            }
            current_node = current_node->next;
        }
    }

    for(int i=0; i< this->bag.nr_elements-1; i++) {
        for (int j = i + 1; j < this->bag.nr_elements; j++) {
            if (!this->bag.r(this->copy_elems[i], this->copy_elems[j])) {
                int aux = this->copy_elems[i];
                this->copy_elems[i] = this->copy_elems[j];
                this->copy_elems[j] = aux;
            }
        }
    }

    this->copy_current_position = 0;
    int first_elem = this->copy_elems[0];
    this->current_position = this->bag.h(first_elem);
    this->current_element = this->bag.hashtable[this->current_position];
}


//BC: Theta(1)
//WC: O(M), where M is the maximum number of distinct elements associated to a key
//Total: O(N)
TComp SortedBagIterator::getCurrent() {
    //TODO - Implementation
    if (!this->valid()) {
        throw std::exception();
    }

    this->current_position = this->bag.h(copy_elems[copy_current_position]);
    struct Node* current_node = this->bag.hashtable[this->current_position];

    while (current_node != NULL && copy_elems[copy_current_position] != current_node->elem) {
        current_node = current_node->next;
    }
    this->current_element = current_node;

    return this->current_element->elem;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
bool SortedBagIterator::valid() {
    //TODO - Implementation
    return (this->copy_current_position != this->bag.nr_elements);
}


//BC: Theta(1)
//WC: O(M), where M is the maximum number of distinct elements associated to a key
//Total: Theta(1)
void SortedBagIterator::next() {
    //TODO - Implementation
    if (!this->valid()) {
        throw std::exception();
    }

    this->copy_current_position++;

    if (this->copy_elems[this->copy_current_position] != copy_elems[this->copy_current_position-1]) {
        this->current_position = this->bag.h(copy_elems[copy_current_position]);
        struct Node* current_node = this->bag.hashtable[this->current_position];

        while (current_node != NULL && copy_elems[copy_current_position] != current_node->elem) {
            current_node = current_node->next;
        }
        this->current_element = current_node;
    }
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
void SortedBagIterator::first() {
    //TODO - Implementation
    this->copy_current_position = 0;
    int first_elem = this->copy_elems[0];
    this->current_position = this->bag.h(first_elem);
    this->current_element = this->bag.hashtable[this->current_position];
}
