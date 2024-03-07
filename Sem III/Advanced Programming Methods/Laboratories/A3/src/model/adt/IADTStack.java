package model.adt;

import java.util.Deque;

import exceptions.GeneralException;

public interface IADTStack<T> extends Iterable<T> {
    T pop() throws GeneralException;

    T peek() throws GeneralException;

    void push(T v);

    boolean isEmpty();

    Deque<T> getStack();
}
