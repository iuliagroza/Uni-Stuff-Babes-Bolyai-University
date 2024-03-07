package model.adt;

import java.util.Map;
import java.util.Set;
import java.util.HashMap;

public class ADTDictionary<T1, T2> implements IADTDictionary<T1, T2> {
    private final HashMap<T1, T2> dictionary;

    public ADTDictionary() {
        dictionary = new HashMap<>();
    }

    @Override
    public void put(T1 key, T2 value) {
        dictionary.put(key, value);
    }

    @Override
    public T2 get(T1 key) {
        return dictionary.get(key);
    }

    @Override
    public boolean containsKey(T1 id) {
        return dictionary.containsKey(id);
    }

    @Override
    public Set<T1> keySet() {
        return dictionary.keySet();
    }

    @Override
    public void remove(T1 key) {
        dictionary.remove(key);
    }

    @Override
    public Map<T1, T2> getDictionary() {
        return dictionary;
    }

    @Override
    public IADTDictionary<T1, T2> copy() {
        IADTDictionary<T1, T2> newDictionary = new ADTDictionary<>();

        for (T1 key : keySet()) {
            newDictionary.put(key, get(key));
        }

        return newDictionary;
    }
}
