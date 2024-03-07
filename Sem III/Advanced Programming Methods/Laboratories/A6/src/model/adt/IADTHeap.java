package model.adt;

import model.values.IValue;
import exceptions.ADTException;

import java.util.Map;

public interface IADTHeap {
    Map<Integer, IValue> getContent();

    void setContent(Map<Integer, IValue> newMap);

    Integer add(IValue value);

    void update(Integer position, IValue value) throws ADTException;

    IValue get(Integer position) throws ADTException;
}