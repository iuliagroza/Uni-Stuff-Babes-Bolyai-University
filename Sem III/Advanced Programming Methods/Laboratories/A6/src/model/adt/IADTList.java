package model.adt;

import java.util.function.Consumer;

public interface IADTList<T> extends Iterable<T> {
    void add(T v);

    @Override
    void forEach(Consumer<? super T> action);

    boolean isEmpty();
}
