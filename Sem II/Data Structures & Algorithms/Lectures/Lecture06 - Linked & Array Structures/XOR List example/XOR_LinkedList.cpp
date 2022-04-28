// XOR Linked List example
// TO DO: separate into h and cpp

#include <iostream>
using namespace std;

typedef int TElem;

// XOR Node
struct XORNode;
typedef XORNode* PXORNode;
struct XORNode
{
	TElem info;
	PXORNode link; /* XOR of next and previous node */
};

// uintptr_t is an unsigned integer type that is capable of storing a data pointer.
// returns XOR-ed value of the node addresses
PXORNode XOR (PXORNode a, PXORNode b)
{
	return (PXORNode) ((uintptr_t) (a) ^ (uintptr_t) (b));
}



class XORList {
private:
	PXORNode head;
	PXORNode tail;

public:
	friend void printListForward (const XORList& l);
	XORList();
	void addToBeginning(TElem elem);
	void freeNodes ();
	~XORList();

};

XORList::XORList(){
	head = nullptr;
	tail = nullptr;
}

XORList::~XORList(){
	freeNodes();
	head = nullptr;
	tail = nullptr;
}


void XORList::addToBeginning(TElem elem)
{
	PXORNode newNode = new XORNode();
	newNode->info = elem;
	newNode->link= head;

	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	} else {
		head->link = XOR(newNode, head->link);
		head = newNode;
	}
}

void XORList::freeNodes ()
{
	PXORNode curr = this->head;
	PXORNode prev = nullptr;
	PXORNode next;

	while (curr != nullptr)
	{
		next = XOR (prev, curr->link);
		if (prev != nullptr) 	delete prev;
		// update prev and curr for next iteration
		prev = curr;
		curr = next;
	}
	if (prev != nullptr)		delete prev;
	this->head = nullptr;
	this->tail = nullptr;
}


//---------------------------------
void printListForward (const XORList& l)
{
	PXORNode curr = l.head;
	PXORNode prev = nullptr;
	PXORNode next;

	while (curr != nullptr)
	{
		std::cout << curr->info << " " ;
		next = XOR(prev, curr->link);
		prev = curr;
		curr = next;
	}
	std::cout <<"<end-of-list> " << endl;
}



int test_XOR_LinkedList ()
{
	XORList l;
	l.addToBeginning(10);
	l.addToBeginning(20);
	l.addToBeginning(30);
	l.addToBeginning(40);

	// print the created list
	printListForward(l);
	l.freeNodes();
	printListForward(l);
	return (0);
}
