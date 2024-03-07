package model.types;

import model.values.IValue;
import model.values.BoolValue;

public class BoolType implements IType {
    @Override
    public boolean equals(IType type) {
        return type instanceof BoolType;
    }

    @Override
    public IValue getDefault() {
        return new BoolValue(false);
    }

    @Override
    public String toString() {
        return "bool";
    }
}
