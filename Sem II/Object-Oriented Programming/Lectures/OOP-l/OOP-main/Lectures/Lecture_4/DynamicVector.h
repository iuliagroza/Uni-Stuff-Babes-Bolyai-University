#pragma once

template<typename T>
class DynamicVector {
private:
    T *elems;
    int size;
    int capacity;

public:
    // default constructor for a DynamicVector
    DynamicVector(int capacity = 10);

    // copy constructor for a DynamicVector
    DynamicVector(const DynamicVector &v);

    ~DynamicVector();

    // assignment operator for a DynamicVector
    DynamicVector &operator=(const DynamicVector &v);

    /*
        Overloading the subscript operator
        Input: pos - a valid position within the vector.
        Output: a reference to the element o position pos.
    */
    T &operator[](int pos);

    // Adds an element to the current DynamicVector.
    void add(T e);

    int getSize() const;

private:
    // Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
    void resize(double factor = 2);
};

template<typename T>
DynamicVector<T>::DynamicVector(int capacity) {
    this->size = 0;
    this->capacity = capacity;
    this->elems = new T[capacity];
}

template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T> &v) {
    // To be implemented...
}

template<typename T>
DynamicVector<T>::~DynamicVector() {
    // To be implemented...
}

template<typename T>
DynamicVector<T> &DynamicVector<T>::operator=(const DynamicVector<T> &v) {
    // To be implemented...
    return DynamicVector<T>(1);
}

template<typename T>
T &DynamicVector<T>::operator[](int pos) {
    // To be implemented...
    T t;
    return t;
}

template<typename T>
void DynamicVector<T>::add(T e) {
    // To be implemented...
}

template<typename T>
void DynamicVector<T>::resize(double factor) {
    // To be implemented...
}

template<typename T>
int DynamicVector<T>::getSize() const {
    // To be implemented...
    return 0;
}