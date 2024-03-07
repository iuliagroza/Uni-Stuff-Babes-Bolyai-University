package model.adt;

import java.util.Deque;
import java.util.Iterator;
import java.util.LinkedList;

import exceptions.GeneralException;

public class ADTStack<T> implements IADTStack<T> {
    private final Deque<T> deque;

    public ADTStack() {
        deque = new LinkedList<>();
    }

    @Override
    public T pop() throws GeneralException {
        if (deque.isEmpty()) {
            throw new GeneralException("Stack Error: Stack is empty.");
        }

        return deque.pop();
    }

    @Override
    public T peek() throws GeneralException {
        if (deque.isEmpty()) {
            throw new GeneralException("Stack Error: Stack is empty.");
        }

        return deque.peek();
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

    @Override
    public Deque<T> getStack() {
        return deque;
    }
}
