package model.type;

import model.value.IntValue;
import model.value.Value;

public class IntType implements Type{
    @Override
    public boolean equals(Type anotherType) {
        return anotherType instanceof IntType;
    }

    @Override
    public Value defaultValue() {
        return new IntValue(0);
    }

    @Override
    public Type deepCopy() {
        return new IntType();
    }

    @Override
    public String toString() {
        return "int";
    }
}
