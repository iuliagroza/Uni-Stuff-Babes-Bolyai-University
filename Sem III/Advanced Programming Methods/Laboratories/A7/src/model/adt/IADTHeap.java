package model.adt;

import exceptions.ADTException;
import model.values.IValue;

import java.util.Map;

public interface IADTHeap {
    Integer getFreeValue();

    Map<Integer, IValue> getContent();

    void setContent(Map<Integer, IValue> newMap);

    Integer add(IValue value);

    void update(Integer position, IValue value) throws ADTException;

    IValue get(Integer position) throws ADTException;
}