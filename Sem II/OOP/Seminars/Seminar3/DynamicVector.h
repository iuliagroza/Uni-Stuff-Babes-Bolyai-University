#pragma once
#include <iterator>

template <typename T>
class DynamicVector
{
private:
	T* elems;
	int size;
	int capacity;

public:
	// default constructor for a DynamicVector
	DynamicVector(int capacity = 10);

	// copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& v);
	~DynamicVector();

	// assignment operator for a DynamicVector
	DynamicVector& operator=(const DynamicVector& v);

	/*
		Overloading the subscript operator
		Input: pos - a valid position within the vector.
		Output: a reference to the element o position pos.
	*/
	// operator[]
    T& operator[](const int position){
        return this->array[position];
    }

	// Adds an element to the current DynamicVector.
	void add(const T& e);

	int getSize() const;
	void setSize(int s) { size = s; }

private:
	// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	void resize(double factor = 2);

public:
	class iterator
	{
	private:
		T* ptr;
	public:
		// constructor with parameter T*
        iterator(T* elem) {
            this->ptr = elem;
        }

		// operator++ - pre-incrementing
        iterator& operator++() {
            ++this->position;
            return *this;
        }

		// operator++ - post-incrementing
        iterator& operator++(int) {
            int aux = this;
            this->position++;
            return aux;
        }

		// dereferencing operator

		// operator!=
        bool operator!=(const iterator &other_iterator)const{
            return this->position != other_iterator.position;
        }
	};

	iterator begin()
	{
		// TODO
        return iterator(& this->elems[0]);
	}

	iterator end()
	{
		// TODO
        return iterator(& this->elems[this->size]);
	}
};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elems = new T[capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& v)
{
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elems;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& v)
{
	if (this == &v)
		return *this;

	this->size = v.size;
	this->capacity = v.capacity;

	delete[] this->elems;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];

	return *this;

}

template <typename T>
void DynamicVector<T>::add(const T& e)
{
	if (this->size == this->capacity)
		this->resize();
	this->elems[this->size] = e;
	this->size++;
}

template <typename T>
void DynamicVector<T>::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	T* els = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elems[i];

	delete[] this->elems;
	this->elems = els;
}

template <typename T>
int DynamicVector<T>::getSize() const
{
	return this->size;
}