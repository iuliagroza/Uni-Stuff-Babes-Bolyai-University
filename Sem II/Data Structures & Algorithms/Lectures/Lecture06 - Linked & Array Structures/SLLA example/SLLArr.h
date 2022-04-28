#pragma once

typedef int TElem;

// this example uses a static array (capacity is fixed, so - no resize)
#define CAP 100
class Iterator;

class SLLA {
private:
    static const int cap=CAP;
	TElem elems[cap];
	int next[cap];
	int head;
	int firstFree;  //firstEmpty

    int allocateP();
    void freeP(int i);

public:
	friend class Iterator;
	SLLA();
	void insertFirst(TElem elem);
	Iterator iterator() const;
	// other operaions
	// ...
	// Remark: nothing here is dynamically allocated

 };



