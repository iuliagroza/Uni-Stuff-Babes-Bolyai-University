#pragma once
#include "Multimap.h"
#include <stack>

class Iterator
{
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual std::pair<std::string, iterator::Castle> currentItem() = 0;
	virtual bool isDone() = 0;
};

class LinkedListIterator : public Iterator
{
private:
	LinkedListMultimap& multimap;
	Node* current;

public:
	LinkedListIterator(LinkedListMultimap& m);
	void first() override;
	void next() override;
	std::pair<std::string, iterator::Castle> currentItem() override;
	bool isDone() override;
};

class BinarySearchTreeIterator : public Iterator
{
private:
	BinarySearchTreeMultimap& multimap;
	TreeNode* current;
	std::stack<TreeNode*> stack;	// stack used for inorder iteration

public:
	BinarySearchTreeIterator(BinarySearchTreeMultimap& m);
	void first() override;
	void next() override;
	std::pair<std::string, iterator::Castle> currentItem() override;
	bool isDone() override;

private:
	void currentToLeftAsMuchAsPossibleAndAddToStack();
};