package model.expressions;

import model.adt.IADTDictionary;
import model.types.IType;
import model.values.IValue;

public class VariableExpression implements IExpression {
    private final String variable;

    public VariableExpression(String variable) {
        this.variable = variable;
    }

    @Override
    public IValue evaluate(IADTDictionary<String, IValue> symbolTable) {
        return symbolTable.get(variable);
    }

    @Override
    public String toString() {
        return String.format("%s", variable);
    }
}
