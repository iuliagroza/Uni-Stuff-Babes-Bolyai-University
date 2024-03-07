package model.types;

import model.values.IValue;
import model.values.ReferenceValue;

public class ReferenceType implements IType {
    private final IType inner;

    public ReferenceType(IType inner) {
        this.inner = inner;
    }

    public IType getInner() {
        return inner;
    }

    @Override
    public boolean equals(IType type) {
        if (type instanceof ReferenceType) {
            return inner.equals(((ReferenceType) type).getInner());
        } else {
            return false;
        }
    }

    @Override
    public String toString() {
        return "Ref(" + inner.toString() + ")";
    }

    @Override
    public IValue getDefault() {
        return new ReferenceValue(0, inner);
    }
}