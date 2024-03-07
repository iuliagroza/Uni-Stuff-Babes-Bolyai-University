package model.adt;

import java.util.function.Consumer;

import exceptions.ADTException;

public interface IADTList<T> extends Iterable<T> {
    T pop() throws ADTException;

    void add(T v);

    @Override
    void forEach(Consumer<? super T> action);

    boolean isEmpty();

    java.util.List<T> getList();
}
