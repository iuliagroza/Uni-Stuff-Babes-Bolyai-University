package model.adt;

import java.util.Map;
import java.util.Set;

public interface IADTDictionary<T1, T2> {
    T2 get(T1 id);

    void remove(T1 key);

    void put(T1 v1, T2 v2);

    boolean containsKey(T1 id);

    Map<T1, T2> getDictionary();

    Set<T1> keySet();

    IADTDictionary<T1, T2> copy();
}
