package model.adt;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.function.Consumer;

import exceptions.GeneralException;

public class ADTList<T> implements IADTList<T> {
    private final java.util.List<T> list;

    public ADTList() {
        list = new LinkedList<>();
    }

    public ADTList(java.util.List<T> list) {
        this.list = list;
    }

    @Override
    public T pop() throws GeneralException {
        synchronized (list) {
            if (list.size() > 0) {
                T newList = list.get(0);
                list.remove(0);
                return newList;
            }
        }
        throw new GeneralException("List Error: List is empty.");
    }

    @Override
    public void add(T v) {
        synchronized (list) {
            list.add(v);
        }
    }

    @Override
    public void forEach(Consumer<? super T> action) {
        synchronized (list) {
            list.forEach(action);
        }
    }

    @Override
    public boolean isEmpty() {
        synchronized (list) {
            return list.isEmpty();
        }
    }

    @Override
    public Iterator<T> iterator() {
        synchronized (list) {
            return list.iterator();
        }
    }

    @Override
    public java.util.List<T> getList() {
        return list;
    }
}
