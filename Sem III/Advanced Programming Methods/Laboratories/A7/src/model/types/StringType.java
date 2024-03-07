package model.types;

import model.values.StringValue;
import model.values.IValue;

public class StringType implements IType {
    @Override
    public boolean equals(IType type) {
        return type instanceof StringType;
    }

    @Override
    public IValue getDefault() {
        return new StringValue("");
    }

    @Override
    public String toString() {
        return "string";
    }
}