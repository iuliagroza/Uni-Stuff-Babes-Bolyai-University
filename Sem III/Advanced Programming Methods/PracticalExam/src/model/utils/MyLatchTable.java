package model.utils;

import exceptions.InterpreterException;

import java.util.HashMap;

public class MyLatchTable implements MyILatchTable{
    private HashMap<Integer, Integer> latchTable;
    private int freeLocation = 0;

    public MyLatchTable() {
        this.latchTable = new HashMap<>();
    }

    @Override
    public void put(int key, int value) throws InterpreterException {
        synchronized (this) {
            if (!latchTable.containsKey(key)) {
                latchTable.put(key, value);
            } else {
                throw new InterpreterException(String.format("Latch table already contains the key %d!", key));
            }
        }
    }

    @Override
    public int get(int key) throws InterpreterException {
        synchronized (this) {
            if (latchTable.containsKey(key)) {
                return latchTable.get(key);
            } else {
                throw new InterpreterException(String.format("Latch table doesn't contain the key %d!", key));
            }
        }
    }

    @Override
    public boolean containsKey(int key) {
        synchronized (this) {
            return latchTable.containsKey(key);
        }
    }

    @Override
    public int getFreeAddress() {
        synchronized (this) {
            freeLocation++;
            return freeLocation;
        }
    }

    @Override
    public void update(int key, int value) throws InterpreterException {
        synchronized (this) {
            if (latchTable.containsKey(key)) {
                latchTable.replace(key, value);
            } else {
                throw new InterpreterException(String.format("Latch table doesn't contain the key %d!", key));
            }
        }
    }

    @Override
    public void setFreeAddress(int freeAddress) {
        synchronized (this) {
            this.freeLocation = freeAddress;
        }
    }

    @Override
    public HashMap<Integer, Integer> getLatchTable() {
        synchronized (this) {
            return latchTable;
        }
    }

    @Override
    public void setLatchTable(HashMap<Integer, Integer> newLatchTable) {
        synchronized (this) {
            this.latchTable = newLatchTable;
        }
    }

    @Override
    public String toString() {
        return latchTable.toString();
    }
}