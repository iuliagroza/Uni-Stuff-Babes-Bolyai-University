package model.values;

import model.types.IType;
import model.types.IntType;

public class IntValue implements IValue {
    private final int value;

    public IntValue(int val) {
        this.value = val;
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    public int getValue() {
        return value;
    }

    @Override
    public String toString() {
        return String.format("%d", value);
    }

    @Override
    public boolean equals(Object object) {
        if (!(object instanceof IntValue)) {
            return false;
        }

        IntValue castObject = (IntValue) object;

        return value == castObject.value;
    }
}
