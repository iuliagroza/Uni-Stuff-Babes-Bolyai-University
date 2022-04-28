// C++ code for inserting element in skip list

#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

typedef int TComp;

class Node;
typedef Node* PNode;

// Class to implement node
class Node
{
private:
	TComp info;
	// Array to hold pointers to node of different level
	PNode *skipLinks;
	int nrSkipLinks;
public:
	friend class SkipList;
	Node(int, int);
};

Node::Node(TComp key, int level)
{
	this->info = key;
	nrSkipLinks = level;
	skipLinks = new PNode[level+1];
	for(int i=0; i<=level;i++) skipLinks[i]=nullptr;
};


// Class for Skip list
class SkipList
{
	PNode head;  // pointer to header node
	int MAX;  // Maximum level for this skip list; -> skip pointers
	int levels;   // current level of skip list: maybe not all MAXLVL are occupied

public:
	SkipList(int); //, float);
	PNode createNode(int, int);
	void insertElement(int);
	void displaySkipList();
	//TO DO: ... deallocate!!
private:
	int randomSkipLevel();
	int flipCoin();
};

SkipList::SkipList(int MAXLVL)
{
	this->MAX = MAXLVL;
	levels = 0;  //?
	// create header node and initialize key to -1
	// this node is a kind of sentinel; key should be never used
	head = new Node(-1, MAXLVL);
};


// flip coin to create random level for node
int SkipList::flipCoin()
{
	return (rand() % 2);         // value in the range 0 to 1
}

// create random of the skip level for node
int SkipList::randomSkipLevel()
{
	int lvl = 0;
	int coinValue = flipCoin();
	while ((coinValue ==1) && (lvl < MAX))
	{
		lvl++;
		coinValue = flipCoin();
	}
	return lvl;
};


// create new node
PNode SkipList::createNode(TComp key, int level)
{
	PNode n = new Node(key, level);
	return n;
};

// Insert given key in skip list
void SkipList::insertElement(TComp key)
{
	int i;

	// create update array and initialize it
	PNode toUpdate[MAX+1];
	for(i=0; i<=MAX;i++) toUpdate[i]=nullptr;

	// search: start from highest level,...  move one level down and continue search
	PNode current = head; // we always have a header
	for (i = levels; i >= 0; i--)
	{
		while (current->skipLinks[i] != NULL &&	current->skipLinks[i]->info < key)
			current = current->skipLinks[i];
		toUpdate[i] = current;
	}
	current = current->skipLinks[0];

	// keep only distinct values
	if (current == NULL || current->info != key)
	{
		int rlevel = randomSkipLevel();
		if (rlevel > levels) 		// If random level is greater than list's current level (node with highest level inserted in list so far),
		{
			for (int i=levels+1;i<rlevel+1;i++)
				toUpdate[i] = head;
			levels = rlevel;
		}
		// insert new node with randomly generated skip levels
		PNode n = createNode(key, rlevel);
		for (int i=0;i<=rlevel;i++)
		{
			n->skipLinks[i] = toUpdate[i]->skipLinks[i];
			toUpdate[i]->skipLinks[i] = n;
		}
		//cout << "Successfully Inserted key " << key << "\n";
	}
};

void SkipList::displaySkipList()
{
	for (int i=0;i<=MAX;i++)
	{
		PNode node = head->skipLinks[i];
		cout << "Level " << i << ": ";
		while (node != NULL)
		{
			cout << node->info<<" ";
			node = node->skipLinks[i];
		}
		cout << "\n";
	}
};

int test_skipList()
{
	srand((unsigned)time(0));

	SkipList lst(7);

	lst.insertElement(1);
	lst.insertElement(7);
	lst.insertElement(16);
	lst.insertElement(25);
	lst.insertElement(23);
	lst.insertElement(19);
	lst.insertElement(5);
	lst.insertElement(3);
	lst.insertElement(14);
	lst.insertElement(15);
	lst.insertElement(25);
	lst.insertElement(11);
	lst.displaySkipList();
	return 0;
}
