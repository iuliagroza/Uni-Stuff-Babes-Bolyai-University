#include "Multimap.h"
#include <map>
#include "Iterator.h"

using namespace std;

LinkedListMultimap::LinkedListMultimap(): first{ nullptr }
{
}

LinkedListMultimap::~LinkedListMultimap()
{
	Node* n = this->first;
	while (n != nullptr)
	{
		Node* p = n;
		n = n->getNext();
		delete p;
	}
}

void LinkedListMultimap::add(std::string key, const Castle& value)
{
	if (this->first == nullptr)
	{
		Node* n = new Node{ pair<string, Castle>(key, value), nullptr };
		this->first = n;
		return;
	}

	// add in the beginning
	if (key < this->first->getKey())
	{
		Node* n = new Node{ pair<string, Castle>(key, value), this->first };
		this->first = n;
		return;
	}

	// search for the right place to add
	Node* p = this->first;
	while (p->getNext() != nullptr && key > p->getNext()->getKey())
		p = p->getNext();
	Node* n = new Node{ pair<string, Castle>(key, value), p->getNext() };
	p->setNext(n);
}

std::unique_ptr<Iterator> LinkedListMultimap::createIterator()
{
	return std::make_unique<LinkedListIterator>(*this);
}


// ----------------------------------------------------------------------------------------------------------------------------------

BinarySearchTreeMultimap::BinarySearchTreeMultimap()
{
	this->root = nullptr;
}

BinarySearchTreeMultimap::~BinarySearchTreeMultimap()
{
	this->destroy(this->root);
}

void BinarySearchTreeMultimap::add(std::string key, const Castle & value)
{
	this->root = this->addRec(this->root, key, value);
}

TreeNode* BinarySearchTreeMultimap::addRec(TreeNode * p, std::string key, const Castle & value)
{
	if (p == nullptr)
		return new TreeNode{ std::pair<std::string, Castle>(key, value), nullptr, nullptr };

	if (key < p->getKey())
		p->setLeft(this->addRec(p->getLeft(), key, value));
	else
		p->setRight(this->addRec(p->getRight(), key, value));

	return p;
}

std::unique_ptr<Iterator> BinarySearchTreeMultimap::createIterator()
{
	return std::make_unique<BinarySearchTreeIterator>(*this);
}

void BinarySearchTreeMultimap::destroy(TreeNode * p)
{
	if (p->getLeft() != nullptr)
		this->destroy(p->getLeft());
	if (p->getRight() != nullptr)
		this->destroy(p->getRight());
	delete p;
}
