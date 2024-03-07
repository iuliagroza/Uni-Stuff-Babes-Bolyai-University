package model.type;

import model.value.Value;

public interface Type {
    boolean equals(Type anotherType);
    Value defaultValue();
    Type deepCopy();
}
