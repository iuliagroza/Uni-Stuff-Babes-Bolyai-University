#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_


typedef int TElem;

class Iterator;
class DynamicArray {

private:
	int cap;
	int nrElem;
	TElem *elems;

	void resize();

public:
	friend class Iterator;

	DynamicArray(int);
	~DynamicArray();

	// use 0-based indexing
	int size() const;
	TElem getElement(int) const;
	void addToEnd(TElem);
	Iterator iterator();

	DynamicArray(const DynamicArray&)=delete;
	DynamicArray& operator=(const DynamicArray&)=delete;

};

class Iterator {

private:

	const DynamicArray& v;
	int current;

	//We could use:
	//TElem *curent;

public:

	Iterator(const DynamicArray&);

	bool valid() const;
	TElem getCurrent() const;
	void next();
	void first();
};






#endif /* DYNAMICARRAY_H_ */
