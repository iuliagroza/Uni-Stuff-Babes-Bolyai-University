package model.utils;

import exceptions.InterpreterException;

import java.util.List;

public interface MyIList<T> {
    void add(T elem);
    T pop() throws InterpreterException;
    boolean isEmpty();
    List<T> getList();
}
