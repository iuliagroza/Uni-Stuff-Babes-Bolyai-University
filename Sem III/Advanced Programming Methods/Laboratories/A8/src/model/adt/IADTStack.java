package model.adt;

import java.util.Deque;
import java.util.List;

import exceptions.ADTException;

public interface IADTStack<T> extends Iterable<T> {
    T pop() throws ADTException;

    T peek() throws ADTException;

    void push(T v);

    boolean isEmpty();

    Deque<T> getStack();

    public List<T> getReversed();
}
