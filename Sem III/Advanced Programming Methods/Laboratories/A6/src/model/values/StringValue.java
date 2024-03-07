package model.values;

import model.types.IType;
import model.types.StringType;

public class StringValue implements IValue {
    private final String value;

    public StringValue(String value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    public String getValue() {
        return value;
    }

    @Override
    public String toString() {
        return value;
    }

    @Override
    public boolean equals(Object object) {
        if (!(object instanceof StringValue)) {
            return false;
        }

        StringValue castObject = (StringValue) object;

        return value.equals(castObject.value);
    }
}