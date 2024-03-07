package model.expressions;

import model.adt.IADTDictionary;
import model.adt.IADTHeap;
import model.types.IType;
import model.values.IValue;

public class ValueExpression implements IExpression {
    private final IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    @Override
    public IValue evaluate(IADTDictionary<String, IValue> symbolTable, IADTHeap heap) {
        return value;
    }

    @Override
    public IType typeCheck(IADTDictionary<String, IType> typeTable) {
        return value.getType();
    }

    @Override
    public String toString() {
        return String.format("%s", value.toString());
    }
}
