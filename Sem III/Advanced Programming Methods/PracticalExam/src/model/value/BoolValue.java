package model.value;

import model.type.BoolType;
import model.type.Type;

public class BoolValue implements Value{
    private final boolean value;

    public BoolValue(boolean value) {
        this.value = value;
    }

    @Override
    public Type getType() {
        return new BoolType();
    }

    @Override
    public boolean equals(Object anotherValue) {
        if (!(anotherValue instanceof BoolValue castValue))
            return false;
        return this.value == castValue.value;
    }

    @Override
    public Value deepCopy() {
        return new BoolValue(value);
    }

    public boolean getValue() {
        return this.value;
    }

    @Override
    public String toString() {
        return this.value ? "true" : "false";
    }
}
