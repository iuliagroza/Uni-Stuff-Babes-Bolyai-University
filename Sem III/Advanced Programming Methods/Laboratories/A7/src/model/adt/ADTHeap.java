package model.adt;

import exceptions.ADTException;
import model.values.IValue;

import java.util.HashMap;
import java.util.Map;

public class ADTHeap implements IADTHeap {
    private final Map<Integer, IValue> map;
    private Integer freeValue;

    public Integer newValue() {
        freeValue += 1;
        if (map.containsKey(freeValue)) {
            freeValue += 1;
        }

        return freeValue;
    }

    public ADTHeap(Map<Integer, IValue> map) {
        this.map = map;
        freeValue = 1;
    }

    public ADTHeap() {
        map = new HashMap<>();
        freeValue = 1;
    }

    @Override
    public Integer getFreeValue() {
        return freeValue;
    }

    @Override
    public Map<Integer, IValue> getContent() {
        return map;
    }

    @Override
    public void setContent(Map<Integer, IValue> newMap) {
        map.clear();
        for (Integer i : newMap.keySet()) {
            map.put(i, newMap.get(i));
        }
    }

    @Override
    public Integer add(IValue value) {
        map.put(freeValue, value);
        Integer toReturn = freeValue;
        freeValue = newValue();
        return toReturn;
    }

    @Override
    public void update(Integer position, IValue value) throws ADTException {
        if (!map.containsKey(position)) {
            throw new ADTException(String.format("Heap Error: %d is not in the heap.", position));
        }

        map.put(position, value);
    }

    @Override
    public IValue get(Integer position) throws ADTException {
        if (!map.containsKey(position)) {
            throw new ADTException(String.format("Heap Error: %s is not in the heap.", position));
        }
        return map.get(position);
    }
}