#pragma once

#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)

class MultiMapIterator;

class MultiMap {
    friend class MultiMapIterator;

private:
    //TODO - Representation
    template<typename TElement>
    struct DLLANode {
        TElement info;
        int prev;
        int next;
    };

    template<typename TElement>
    struct DLLA {
        DLLANode<TElement> *nodes;
        int capacity;
        int size;
        int first_free;
        int head;
        int tail;

        DLLA() {
            capacity = 2;
            size = 0;
            first_free = 0;
            head = -1;
            tail = -1;

            nodes = new DLLANode<TElement>[capacity];
            for (int index = 0; index < capacity - 1; index++) {
                nodes[index].next = index + 1;
                nodes[index].prev = index - 1;
            }
            nodes[capacity - 1].next = -1;
            nodes[capacity - 1].prev = capacity - 2;
        }

        ~DLLA() {
            if (nodes == nullptr) {
                return;
            }
            nodes = nullptr;
        }
    };

    DLLA<pair<TKey, DLLA<TValue>>> keys;
    int number_of_pairs;
public:
    //constructor
    MultiMap();

    template<typename TElement>
    void resize(DLLA<TElement> &dlla);

    template<typename TElement, typename TVal>
    void add_to_dlla(DLLA<TElement> &dlla, TVal v);

    //adds a key value pair to the multimap
    void add(TKey c, TValue v);

    template<typename TElement>
    bool delete_dlla(DLLA<TElement> &dlla, int position);

    //removes a key value pair from the multimap
    //returns true if the pair was removed (if it was in the multimap) and false otherwise
    bool remove(TKey c, TValue v);

    //returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
    vector <TValue> search(TKey c) const;

    //returns the number of pairs from the multimap
    int size() const;

    //checks whether the multimap is empty
    bool isEmpty() const;

    //returns a vector with all the keys from the MultiMap
    vector<TKey> keySet() const;

    //returns an iterator for the multimap
    MultiMapIterator iterator() const;

    //desctructor
    ~MultiMap();

};

