package model.utils;

import exceptions.InterpreterException;
import model.value.Value;

import java.util.HashMap;
import java.util.Set;

public class MyHeap implements MyIHeap{
    HashMap<Integer, Value> heap;
    Integer freeLocationValue;

    public int newValue() {
        freeLocationValue += 1;
        while (freeLocationValue == 0 || heap.containsKey(freeLocationValue))
            freeLocationValue += 1;
        return freeLocationValue;
    }

    public MyHeap() {
        this.heap = new HashMap<>();
        freeLocationValue = 1;
    }

    @Override
    public int getFreeValue() {
        synchronized (this) {
            return freeLocationValue;
        }
    }

    @Override
    public HashMap<Integer, Value> getContent() {
        synchronized (this) {
            return heap;
        }
    }

    @Override
    public void setContent(HashMap<Integer, Value> newMap) {
        synchronized (this) {
            this.heap = newMap;
        }
    }

    @Override
    public int add(Value value) {
        synchronized (this) {
            heap.put(freeLocationValue, value);
            Integer toReturn = freeLocationValue;
            freeLocationValue = newValue();
            return toReturn;
        }
    }

    @Override
    public void update(Integer position, Value value) throws InterpreterException {
        synchronized (this) {
            if (!heap.containsKey(position))
                throw new InterpreterException(String.format("%d is not present in the heap", position));
            heap.put(position, value);
        }
    }

    @Override
    public Value get(Integer position) throws InterpreterException {
        synchronized (this) {
            if (!heap.containsKey(position))
                throw new InterpreterException(String.format("%d is not present in the heap", position));
            return heap.get(position);
        }
    }

    @Override
    public boolean containsKey(Integer position) {
        synchronized (this) {
            return this.heap.containsKey(position);
        }
    }

    @Override
    public void remove(Integer key) throws InterpreterException {
        synchronized (this) {
            if (!containsKey(key))
                throw new InterpreterException(key + " is not defined.");
            freeLocationValue = key;
            this.heap.remove(key);
        }
    }

    @Override
    public Set<Integer> keySet() {
        synchronized (this) {
            return heap.keySet();
        }
    }
    @Override
    public String toString() {
        return this.heap.toString();
    }

}
