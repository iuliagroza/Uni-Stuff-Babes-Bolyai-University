#include "ListIterator.h"
#include <exception>

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
SortedIndexedList::SortedIndexedList(Relation r) {
    //TODO - Implementation
    this->r = r;
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
int SortedIndexedList::size() const {
    //TODO - Implementation
    return this->sorted_list.getSize();
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
bool SortedIndexedList::isEmpty() const {
    //TODO - Implementation
    return size() == 0;
}

TComp SortedIndexedList::getElement(int i) const {
    //TODO - Implementation
    if (i >= size()) {
        throw std::exception();
    }

    Node *current = this->sorted_list.getHead();

    int position = 0;
    while (position < i && current != nullptr) {
        current = current->next;
        position++;
    }

    return current->data;
}

//BC: Theta(1)
//WC: Theta(N), where N is the number of elements the Sorted List has
//Total: O(N)
TComp SortedIndexedList::remove(int i) {
    //TODO - Implementation
    if (i == -1 || i >= size()) {
        throw std::exception();
    }

    Node *previous_node = nullptr;
    Node *current_node = this->sorted_list.getHead();

    int current_position = 0;
    while (current_position < i && current_node != nullptr) {
        previous_node = current_node;
        current_node = current_node->next;
        current_position++;
    }

    if (previous_node == nullptr && current_node != nullptr) {
        this->sorted_list.setHead(current_node->next);
        this->sorted_list.setSize(this->sorted_list.getSize() - 1);
    } else if (current_node != nullptr) {
        previous_node->next = current_node->next;
        current_node->next = nullptr;
        this->sorted_list.setSize(this->sorted_list.getSize() - 1);
    }
    return current_node->data;
}

//BC: Theta(1)
//WC: Theta(N), where N is the number of elements the Sorted List has
//Total: O(N)
int SortedIndexedList::search(TComp e) const {
    //TODO - Implementation
    Node *current = this->sorted_list.getHead();

    int position = 0;
    while (current != nullptr && current->data != e) {
        current = current->next;
        position++;
    }

    if (position == size()) {
        return -1;
    }
    return position;
}

//BC: Theta(1)
//WC: Theta(N), where N is the number of elements the Sorted List has
//Total: O(N)
void SortedIndexedList::add(TComp e) {
    //TODO - Implementation
    Node *current = this->sorted_list.getHead();

    int position = 0;
    while (current != nullptr && !this->r(e, current->data)) {
        current = current->next;
        position++;
    }

    if (position == 0) {
        Node *new_node = new Node();
        new_node->data = e;
        new_node->next = this->sorted_list.getHead();

        this->sorted_list.setHead(new_node);
        this->sorted_list.setSize(this->sorted_list.getSize() + 1);
    } else {
        Node *current_node = this->sorted_list.getHead();

        int current_position = 0;
        while (current_position < (position - 1) && current_node != nullptr) {
            current_node = current_node->next;
            current_position++;
        }
        if (current_node != nullptr) {
            Node *new_node = new Node();
            new_node->data = e;
            new_node->next = current_node->next;

            current_node->next = new_node;
            this->sorted_list.setSize(this->sorted_list.getSize() + 1);
        }
    }
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
ListIterator SortedIndexedList::iterator() {
    return ListIterator(*this);
}

//BC: Theta(N), where N is the number of elements the Sorted List has
//WC: Theta(N)
//Total: Theta(N)
//destructor
SortedIndexedList::~SortedIndexedList() {
    //TODO - Implementation
    Node *current = this->sorted_list.getHead();
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

//BC: Theta(N), where N is the number of elements the Sorted List has
//WC: Theta(N)
//Total: Theta(N)
void SortedIndexedList::filter(Condition cond) {
    Node *current = this->sorted_list.getHead();
    int pos = 0;
    while (current != nullptr && cond(current->data)) {
        pos++;
        current = current->next;
    }

    int times = this->sorted_list.getSize() - pos;

    while(times != 0) {
        remove(pos);
        times--;
    }
}