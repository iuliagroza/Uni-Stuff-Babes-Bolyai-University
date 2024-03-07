package model.adt;

import exceptions.ADTException;

public interface IADTStack<T> extends Iterable<T> {
    T pop() throws ADTException;

    void push(T v);

    boolean isEmpty();
}
