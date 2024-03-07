package model.expressions;

import model.adt.IADTDictionary;
import model.types.IType;
import model.values.IValue;
import exceptions.ExpressionException;

public interface IExpression {
    IValue evaluate(IADTDictionary<String, IValue> symbolTable) throws ExpressionException;
}
