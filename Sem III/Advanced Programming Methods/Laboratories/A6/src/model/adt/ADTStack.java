package model.adt;

import exceptions.ADTException;

import java.util.Deque;
import java.util.Iterator;
import java.util.LinkedList;

public class ADTStack<T> implements IADTStack<T> {
    private final Deque<T> deque;

    public ADTStack() {
        deque = new LinkedList<>();
    }

    @Override
    public T pop() throws ADTException {
        if (deque.isEmpty()) {
            throw new ADTException("Stack Error: Stack is empty.");
        }

        return deque.pop();
    }

    @Override
    public void push(T v) {
        deque.push(v);
    }

    @Override
    public boolean isEmpty() {
        return deque.isEmpty();
    }

    @Override
    public Iterator<T> iterator() {
        return deque.iterator();
    }
}
