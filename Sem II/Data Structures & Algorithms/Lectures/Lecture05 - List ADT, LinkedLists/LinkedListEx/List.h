#pragma once

typedef int TElem;

class ListIterator;

class List {
private:
	struct SLLNode;
	typedef SLLNode *PNode;
//	struct SLLNode	{
//			TElem info;
//			PNode next;
//			SLLNode(TElem e, PNode n);
//	};

	PNode head;

public:
	friend class ListIterator;
	List();

	void addToBeginning(TElem elem);

	// --> see: IteratedList
	// changes the element from the current position to the given one.
	//returns the old value from the position
	//throws exception if the position is not valid
	TElem setElement(ListIterator pos, TElem e);

	//other operations
	// ...	ListIterator iterator() const;
	~List();

	List(const List&)=delete;
	List& operator=(const List&)=delete;

};

class ListIterator {
	friend class List;
private:	ListIterator(const List& l);

	const List& list;
	List::PNode currentElement;

public:

    friend class List;
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;

};


