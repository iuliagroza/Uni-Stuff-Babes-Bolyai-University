package model.values;

import model.types.IType;
import model.types.ReferenceType;

public class ReferenceValue implements IValue {
    private final int address;
    private final IType locationType;

    public ReferenceValue(int address, IType locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public int getAddress() {
        return address;
    }

    public IType getLocationType() {
        return locationType;
    }

    @Override
    public IType getType() {
        return new ReferenceType(locationType);
    }

    @Override
    public String toString() {
        return String.format("(%d, %s)", address, locationType);
    }
}