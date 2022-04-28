#include "Iterator.h"
#include <iostream>
#include "SLLArr.h"


SLLA::SLLA() {
	// empty list
	head = -1;
	//initialize free space
	for(int i=0;i<cap-1;i++)
        next[i]=i+1;
    next[cap-1]=-1;
	firstFree = 0;
}

int SLLA::allocateP() {
	// in case of DynArray we would resize the array; here - just return -1
	if (firstFree == -1) return -1;

	int newFreePos=firstFree;
    firstFree=next[firstFree];
    return newFreePos;
}

void SLLA::freeP(int i) {
    next[i]=firstFree;
    firstFree=i;
}


void SLLA::insertFirst(TElem e) {
	int i=allocateP();
    //we used a static array, it is possible to be full,
	// if we get -1 when trying to allocate - then: do nothing
    if (i!=-1){
        elems[i]=e;
        next[i]=head;
        head = i;
    }
}

Iterator SLLA::iterator() const {
	return Iterator(*this);
}

