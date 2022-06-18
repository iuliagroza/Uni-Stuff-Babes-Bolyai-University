#pragma once
#include <string>
#include <memory>
#include "Castle.h"

using namespace iterator;

class Iterator;

class Multimap
{
public:
	virtual void add(std::string key, const iterator::Castle& value) = 0;
	virtual std::unique_ptr<Iterator> createIterator() = 0;
	virtual ~Multimap() {}
};

// Linked list Multimap
class Node
{
private:
	std::pair<std::string, iterator::Castle> element;
	Node* next;

public:
	Node(std::pair<std::string, iterator::Castle> elem, Node* n) : element{ elem }, next{ n } {}
	std::string getKey() const { return this->element.first; }
	iterator::Castle getValue() const { return this->element.second; }
	Node* getNext() const { return this->next; }
	void setNext(Node* n) { this->next = n; }
};

class LinkedListMultimap: public Multimap
{
private:
	Node* first;

public:
	LinkedListMultimap();
	~LinkedListMultimap();
	void add(std::string key, const iterator::Castle& value) override;
	std::unique_ptr<Iterator> createIterator() override;

	Node* getFirst() { return this->first; }
};

// Binary Search Tree Multimap
class TreeNode
{
private:
	std::pair<std::string, iterator::Castle> element;
	TreeNode* left;
	TreeNode* right;

public:
	TreeNode(std::pair<std::string, iterator::Castle> elem, TreeNode* l, TreeNode* r) : element{ elem }, left{ l }, right{ r } {}
	std::string getKey() const { return this->element.first; }
	iterator::Castle getValue() const { return this->element.second; }
	TreeNode* getLeft() const { return this->left; }
	void setLeft(TreeNode* n) { this->left = n; }
	TreeNode* getRight() const { return this->right; }
	void setRight(TreeNode* n) { this->right = n; }
};

class BinarySearchTreeMultimap : public Multimap
{
private:
	TreeNode* root;

public:
	BinarySearchTreeMultimap();
	~BinarySearchTreeMultimap();
	void add(std::string key, const iterator::Castle& value) override;
	std::unique_ptr<Iterator> createIterator() override;

	TreeNode* getRoot() { return this->root; }

private:
	TreeNode* addRec(TreeNode* p, std::string key, const iterator::Castle& value);
	void destroy(TreeNode* p);
};