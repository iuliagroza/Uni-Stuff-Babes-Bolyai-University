#ifndef A5_6_IULIAGROZA_DYNAMICARRAY_H
#define A5_6_IULIAGROZA_DYNAMICARRAY_H

template<typename T>
class DynamicArray {
public:
    /*
     * Default constructor
     */
    DynamicArray(int capacity = 10);

    /*
     * Copy by reference constructor
     */
    DynamicArray(const DynamicArray &v);

    /*
     * Destructor
     */
    ~DynamicArray();

private:
    T *elems;
    int size;
    int capacity;

public:
    /*
     * Operator that facilitates the assignment of a DynamicArray object to another DynamicArray
     * object by reference.
     */
    DynamicArray &operator=(const DynamicArray &v);

    /*
     * GETTERS
     */
    int get_size() const;

    T get_element(int pos);

    /*
     * Function that implements the addition functionality. If the size of the array reaches its capacity,
     * the array will be resized (the capacity will double by default).
     * :e: const reference to a TElement element (object)
     */
    void add(const T &e);

    /*
     * Function that implements the removal functionality. The deleted element will be deallocated.
     * :pos: positive integer (smaller than the size of the array)
     */
    void remove(int pos);

    /*
     * Function that implements the removal functionality. It will use the custom assignment operator.
     * :pos: positive integer (smaller than the size of the array)
     * :new_e: const reference to a TElement element (object)
     */
    void update(int pos, const T &new_e);

private:
    /*
     * Resize function that by default doubles the capacity of the array when its size reaches its capacity.
     * :factor: positive integer (by default 2)
     */
    void resize(int factor = 2);
};

template<typename T>
DynamicArray<T>::DynamicArray(int capacity) {
    this->size = 0;
    this->capacity = capacity;
    this->elems = new T[capacity];
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &v) {
    this->size = v.size;
    this->capacity = v.capacity;
    this->elems = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->elems[i] = v.elems[i];
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->elems;
}

template<typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &v) {
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

template<typename T>
int DynamicArray<T>::get_size() const {
    return this->size;
}

template<typename T>
T DynamicArray<T>::get_element(int pos) {
    return this->elems[pos];
}

template<typename T>
void DynamicArray<T>::add(const T &e) {
    if (this->size == this->capacity)
        this->resize();
    this->elems[this->size] = e;
    this->size++;
}

template<typename T>
void DynamicArray<T>::remove(int pos) {
    for (int i = pos; i < this->size - 1; i++) {
        this->elems[i] = this->elems[i + 1];
    }
    this->size--;
}

template<typename T>
void DynamicArray<T>::update(int pos, const T &new_e) {
    this->elems[pos] = new_e;
}

template<typename T>
void DynamicArray<T>::resize(int factor) {
    this->capacity *= factor;

    auto *els = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        els[i] = this->elems[i];

    delete[] this->elems;
    this->elems = els;
}

#endif
