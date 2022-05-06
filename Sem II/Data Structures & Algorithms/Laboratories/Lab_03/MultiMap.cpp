#include "MultiMap.h"
#include "MultiMapIterator.h"

using namespace std;


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
MultiMap::MultiMap() {
    //TODO - Implementation
    this->number_of_pairs = 0;
}


//BC: Theta(N), where N is the number of keys
//WC: Theta(N)
//Total: Theta(N)
template<typename TElement>
void MultiMap::resize(DLLA<TElement> &dlla) {
    dlla.capacity *= 2;

    DLLANode<TElement> *aux = new DLLANode<TElement>[dlla.capacity];
    for (int index = 0; index < dlla.capacity / 2; index++) {
        aux[index] = dlla.nodes[index];
    }

    for (int index = dlla.capacity / 2; index < dlla.capacity; index++) {
        aux[index].next = index + 1;
        aux[index].prev = index - 1;
    }
    aux[dlla.capacity - 1].next = -1;
    dlla.first_free = dlla.capacity / 2;
    dlla.nodes = aux;
}


//BC: Theta(1)
//WC: O(N), where N is the number of keys
//Total: O(N)
template<typename TElement, typename TVal>
void MultiMap::add_to_dlla(DLLA<TElement> &dlla, TVal v) {
    if (dlla.head == -1) {
        dlla.head = dlla.first_free;
        dlla.tail = dlla.first_free;
        dlla.nodes[dlla.head].info = v;

        dlla.first_free = dlla.nodes[dlla.first_free].next;
        dlla.nodes[dlla.head].next = -1;
        dlla.size++;
        return;
    }

    if (dlla.size == dlla.capacity) {
        this->resize(dlla);
    }

    dlla.nodes[dlla.tail].next = dlla.first_free;
    dlla.nodes[dlla.first_free].prev = dlla.tail;

    dlla.tail = dlla.first_free;
    dlla.first_free = dlla.nodes[dlla.tail].next;

    dlla.nodes[dlla.tail].info = v;
    dlla.nodes[dlla.tail].next = -1;

    dlla.size++;
}


//BC: Theta(1)
//WC: Theta(N), where N is the number of keys
//Total: O(N)
void MultiMap::add(TKey c, TValue v) {
    //TODO - Implementation
    if (!this->isEmpty()) {
        int current = this->keys.head;
        while (current != -1) {
            if (this->keys.nodes[current].info.first == c) {
                this->add_to_dlla(this->keys.nodes[current].info.second, v);
                this->number_of_pairs++;
                return;
            }
            current = this->keys.nodes[current].next;
        }
    }

    DLLA<TValue> new_key;
    this->add_to_dlla(new_key, v);
    this->add_to_dlla(this->keys, pair<TKey, DLLA<TValue> >(c, new_key));
    this->number_of_pairs++;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
template<typename TElement>
bool MultiMap::delete_dlla(DLLA<TElement> &dlla, int position) {
    if (position == dlla.tail) {
        dlla.tail = dlla.nodes[dlla.tail].prev;
        dlla.nodes[dlla.tail].next = -1;
    } else {
        if (position == dlla.head) {
            dlla.head = dlla.nodes[position].next;
            dlla.nodes[dlla.head].prev = -1;
        } else {
            int prev_position = dlla.nodes[position].prev;
            int next_position = dlla.nodes[position].next;
            dlla.nodes[prev_position].next = next_position;
            dlla.nodes[next_position].prev = prev_position;
        }
    }

    dlla.nodes[position].prev = -1;
    dlla.nodes[position].next = dlla.first_free;
    dlla.first_free = position;
    dlla.size--;

    if (dlla.size == 0) {
        dlla.head = -1;
    }

    return true;
}


//BC: Theta(1)
//WC: O(N*M), where N is the number of keys and M is the maximum number of values for a key
//Total: O(N*M)
bool MultiMap::remove(TKey c, TValue v) {
    //TODO - Implementation
    if (this->isEmpty()) {
        return false;
    }

    int current = this->keys.head;
    while (current != -1) {
        if (this->keys.nodes[current].info.first == c) {
            int index = this->keys.nodes[current].info.second.head;
            while (index != -1) {
                if (this->keys.nodes[current].info.second.nodes[index].info == v) {
                    this->delete_dlla(this->keys.nodes[current].info.second, index);
                    this->number_of_pairs--;
                    if (this->keys.nodes[current].info.second.size == 0) {
                        this->delete_dlla(this->keys, current);
                    }
                    return true;
                }
                index = this->keys.nodes[current].info.second.nodes[index].next;
            }
            return 0;
        }
        current = this->keys.nodes[current].next;
    }
    return 0;
}


//BC: Theta(1)
//WC: O(N+M), where N is the number of keys and M is the maximum number of values for a key
//Total: O(N+M)
vector <TValue> MultiMap::search(TKey c) const {
    //TODO - Implementation
    if (this->isEmpty()) {
        return vector<TValue>();
    }

    int current = this->keys.head;
    while (current != -1) {
        if (this->keys.nodes[current].info.first == c) {
            vector <TValue> values;
            int index = this->keys.nodes[current].info.second.head;
            while (index != -1) {
                values.push_back(this->keys.nodes[current].info.second.nodes[index].info);
                index = this->keys.nodes[current].info.second.nodes[index].next;
            }
            return values;
        }
        current = this->keys.nodes[current].next;
    }
    return vector<TValue>();
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
int MultiMap::size() const {
    //TODO - Implementation
    return this->number_of_pairs;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
bool MultiMap::isEmpty() const {
    //TODO - Implementation
    if (this->keys.head == -1) {
        return true;
    }
    return false;
}

//BC: Theta(1)
//WC: O(N^2), where N is the number of keys
//Total: O(N^2)
vector<TKey> MultiMap::keySet() const {
    if (this->isEmpty()) {
        return vector<TValue>();
    }

    vector<TKey> keys_set;
    int current = this->keys.head;
    while (current != -1) {
        bool found = false;
        for(auto key : keys_set) {
            if(this->keys.nodes[current].info.first == key) {
                found = true;
                break;
            }
        }
        if(!found) {
            keys_set.push_back(this->keys.nodes[current].info.first);
        }
        current = this->keys.nodes[current].next;
    }
    return keys_set;
}

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    //TODO - Implementation
}
