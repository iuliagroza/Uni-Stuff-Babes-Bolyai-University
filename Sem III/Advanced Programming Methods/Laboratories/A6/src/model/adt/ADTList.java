package model.adt;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.function.Consumer;

public class ADTList<T> implements IADTList<T> {
    private final java.util.List<T> list;

    public ADTList() {
        list = new LinkedList<>();
    }

    @Override
    public void add(T v) {
        list.add(v);
    }

    @Override
    public void forEach(Consumer<? super T> action) {
        list.forEach(action);
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    @Override
    public Iterator<T> iterator() {
        return list.iterator();
    }
}
