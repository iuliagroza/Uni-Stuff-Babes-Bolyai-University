package model.utils;

import exceptions.InterpreterException;

import java.util.List;

public interface MyIStack<T> {
    T pop() throws InterpreterException;
    void push(T element);
    T peek();
    boolean isEmpty();
    List<T> getReversed();
}
