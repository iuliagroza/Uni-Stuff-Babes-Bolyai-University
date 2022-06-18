#include <cstddef>
#include "SortedBag.h"
#include "SortedBagIterator.h"


//BC: Theta(C)
//WC: Theta(C), where C is the capacity of the hashtable
//Total: Theta(C)
SortedBag::SortedBag(Relation r) {
    //TODO - Implementation
    this->r = r;
    this->m = 127;
    this->nr_elements = 0;

    this->hashtable = new struct Node*[this->m];
    for (int i = 0; i < this->m; i++) {
        this->hashtable[i] = NULL;
    }
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
TComp SortedBag::h(TComp k) const {
    int modulo = k % this->m;
    return (modulo < 0) ? (modulo + this->m) : modulo;
}


//BC: Theta(M)
//WC: Theta(M), where M is the maximum number of distinct elements associated to a key
//Total: Theta(M)
void SortedBag::resize() {
    this->m *= 2;

    TComp* copy_elems = new TComp[this->nr_elements];
    int* copy_freq = new int[this->nr_elements];
    int k = 0;
    for (int i = 0; i < this->m / 2; i++) {
        struct Node *current_node = this->hashtable[i];
        while (current_node != NULL) {
            copy_elems[k] = current_node->elem;
            copy_freq[k++] = current_node->freq;
            current_node = current_node->next;
        }
    }

    for (int i = 0; i < this->m / 2; i++) {
        struct Node* current_node = this->hashtable[i];
        while (current_node != NULL) {
            struct Node* next_node = current_node->next;
            delete current_node;
            current_node = next_node;
        }
    }
    delete[] this->hashtable;

    this->nr_elements = 0;
    this->hashtable = new struct Node* [this->m];
    for (int i = 0; i < this->m; i++) {
        this->hashtable[i] = NULL;
    }

    for (int i = 0; i < k; i++) {
        for(int j = 0; j < copy_freq[i]; j++) {
            this->add(copy_elems[i]);
        }
    }

    delete[] copy_elems;
}


//BC: O(M),
//WC: O(M), where M is the maximum number of distinct elements associated to a key
//Total: O(M)
void SortedBag::add(TComp e) {
    //TODO - Implementation
    auto load_factor = this->nr_elements / this->m;
    if (load_factor >= 1) {
        this->resize();
    }

    TComp position = this->h(e);

    struct Node* current_node = this->hashtable[position];

    while (current_node != NULL && e != current_node->elem) {
        current_node = current_node->next;
    }

    if(current_node != NULL) {
        current_node->freq++;
    } else {
        current_node = this->hashtable[position];
        struct Node* prev_node = NULL;

        struct Node* new_node = new struct Node;
        new_node->elem = e;
        new_node->freq = 1;

        while (current_node != NULL && !r(e, current_node->elem)) {
            prev_node = current_node;
            current_node = current_node->next;
        }

        if (prev_node == NULL) {
            new_node->next = this->hashtable[position];
            this->hashtable[position] = new_node;
        } else {
            new_node->next = current_node;
            prev_node->next = new_node;
        }
    }

    this->nr_elements++;
}


//BC: Theta(1)
//WC: O(M), where M is the maximum number of distinct elements associated to a key
//Total: O(M)
bool SortedBag::remove(TComp e) {
    //TODO - Implementation
    TComp position = this->h(e);
    struct Node* current_node = this->hashtable[position];
    struct Node* prev_node = NULL;

    while (current_node != NULL && e != current_node->elem) {
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (current_node != NULL) {
        if(current_node->freq == 1) {
            if (prev_node == NULL) {
                this->hashtable[position] = this->hashtable[position]->next;
            } else {
                prev_node->next = current_node->next;
            }
        } else {
            current_node->freq--;
        }
        this->nr_elements--;
        return true;
    }
    else {
        return false;
    }
}


//BC: Theta(1)
//WC: O(M), where M is the maximum number of distinct elements associated to a key
//Total: O(M)

bool SortedBag::search(TComp elem) const {
    //TODO - Implementation
    TComp position = this->h(elem);
    struct Node* current_node = this->hashtable[position];

    while (current_node != NULL && elem != current_node->elem) {
        current_node = current_node->next;
    }

    return (current_node != NULL);
}


//BC: Theta(1)
//WC: O(M), where M is the maximum number of distinct elements associated to a key
//Total: O(M)
int SortedBag::nrOccurrences(TComp elem) const {
    //TODO - Implementation
    TComp position = this->h(elem);
    struct Node* current_node = this->hashtable[position];

    while (current_node != NULL && elem != current_node->elem) {
        current_node = current_node->next;
    }

    return (current_node != NULL) ? current_node->freq : 0;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
int SortedBag::size() const {
    //TODO - Implementation
    return this->nr_elements;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
bool SortedBag::isEmpty() const {
    //TODO - Implementation
    return (this->nr_elements == 0);
}


SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}


//BC: Theta(N), where N is the number of elements
//WC: Theta(N)
//Total: Theta(N)
SortedBag::~SortedBag() {
    //TODO - Implementation
    for (int i = 0; i < this->m / 2; i++) {
        struct Node* current_node = this->hashtable[i];
        while (current_node != NULL) {
            struct Node* next_node = current_node->next;
            delete current_node;
            current_node = next_node;
        }
    }
    delete[] this->hashtable;
}


//BC: Theta(N), where N is the number of elements
//WC: Theta(N)
//Total: Theta(N)
void SortedBag::addAll(const SortedBag &b) {
    for (int i = 0; i < b.m; i++) {
        struct Node* current_node = b.hashtable[i];
        while (current_node != NULL) {
            for(int j=0; j<current_node->freq; j++) {
                this->add(current_node->elem);
            }
            current_node = current_node->next;
        }
    }
}