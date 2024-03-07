package model.values;

import model.types.IType;
import model.types.BoolType;

public class BoolValue implements IValue {
    private final boolean value;

    public BoolValue(boolean value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    public boolean getValue() {
        return value;
    }

    @Override
    public String toString() {
        return value ? "true" : "false";
    }

    @Override
    public boolean equals(Object object) {
        if (!(object instanceof BoolValue)) {
            return false;
        }

        BoolValue castObject = (BoolValue) object;

        return value == castObject.value;
    }
}
