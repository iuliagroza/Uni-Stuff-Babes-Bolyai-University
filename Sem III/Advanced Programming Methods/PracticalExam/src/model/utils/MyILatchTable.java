package model.utils;

import exceptions.InterpreterException;

import java.util.HashMap;

public interface MyILatchTable {
    void put(int key, int value) throws InterpreterException;
    int get(int key) throws InterpreterException;
    boolean containsKey(int key);
    int getFreeAddress();
    void update(int key, int value) throws InterpreterException;
    void setFreeAddress(int freeAddress);
    HashMap<Integer, Integer> getLatchTable();
    void setLatchTable(HashMap<Integer, Integer> newLatchTable);
}