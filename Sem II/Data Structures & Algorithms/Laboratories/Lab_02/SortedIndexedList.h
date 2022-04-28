#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;

typedef int TComp;

typedef bool (*Relation)(TComp, TComp);

//takes as a parameter a TComp and returns true or false depending on whether the element respects the condition
typedef bool (*Condition)(TComp);

#define NULL_TCOMP -11111

class Node {
public:
    TComp data;
    Node *next;
};

class SLL {
private:
    Node *head;
    int size;

public:
    SLL() {
        this->head = nullptr;
        this->size = 0;
    }

    Node *getHead() const {
        return this->head;
    }

    int getSize() const {
        return this->size;
    }

    void setHead(Node *newNode) {
        this->head = newNode;
    }

    void setSize(int newSize) {
        this->size = newSize;
    }
};

class SortedIndexedList {
private:
    friend class ListIterator;

private:
    //TODO - Representation
    SLL sorted_list{};
    Relation r;

public:
    // constructor
    SortedIndexedList(Relation r);

    // returns the size of the list
    int size() const;

    //checks if the list is empty
    bool isEmpty() const;

    // returns an element from a position
    //throws exception if the position is not valid
    TComp getElement(int pos) const;

    // adds an element in the sortedList (to the corresponding position)
    void add(TComp e);

    // removes an element from a given position
    //returns the removed element
    //throws an exception if the position is not valid
    TComp remove(int pos);

    // searches for an element and returns the first position where the element appears or -1 if the element is not in the list
    int search(TComp e) const;

    // returns an iterator set to the first element of the list or invalid if the list is empty
    ListIterator iterator();

    //destructor
    ~SortedIndexedList();

    //keeps in the SortedList only the elements that respect the given condition
    void filter(Condition cond);
};
