#include "Iterator.h"

using namespace  iterator;

LinkedListIterator::LinkedListIterator(LinkedListMultimap & m): multimap{m}
{
	this->current = this->multimap.getFirst();
}

void LinkedListIterator::first()
{
	this->current = this->multimap.getFirst();
}

void LinkedListIterator::next()
{
	if (this->current == nullptr)
		return;
	this->current = this->current->getNext();
}

std::pair<std::string, Castle> LinkedListIterator::currentItem()
{
	if (this->current == nullptr)
		std::pair<std::string, Castle>{};
	return std::pair<std::string, Castle>{this->current->getKey(), this->current->getValue()};
}

bool LinkedListIterator::isDone()
{
	return (this->current == nullptr);
}

// ----------------------------------------------------------------------------------------------------------------------

BinarySearchTreeIterator::BinarySearchTreeIterator(BinarySearchTreeMultimap & m): multimap{ m }
{
	this->current = this->multimap.getRoot();
	this->currentToLeftAsMuchAsPossibleAndAddToStack();
}

void BinarySearchTreeIterator::first()
{
	// clear the stack
	while (!stack.empty())
		stack.pop();

	this->current = this->multimap.getRoot();
	this->currentToLeftAsMuchAsPossibleAndAddToStack();
}

void BinarySearchTreeIterator::next()
{
	this->currentToLeftAsMuchAsPossibleAndAddToStack();
}

std::pair<std::string, Castle> BinarySearchTreeIterator::currentItem()
{
	if (!this->stack.empty())
	{
		this->current = this->stack.top();
		this->stack.pop();
	}
	std::pair<std::string, Castle> currentElem = std::pair<std::string, Castle>{this->current->getKey(), this->current->getValue()};
	this->current = this->current->getRight();
	return currentElem;
}

bool BinarySearchTreeIterator::isDone()
{
	return stack.empty();
}

void BinarySearchTreeIterator::currentToLeftAsMuchAsPossibleAndAddToStack()
{
	while (this->current != nullptr)
	{
		stack.push(this->current);
		this->current = this->current->getLeft();
	}
}
