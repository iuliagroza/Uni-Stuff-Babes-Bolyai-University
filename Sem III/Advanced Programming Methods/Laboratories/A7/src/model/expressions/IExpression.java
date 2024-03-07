package model.expressions;

import exceptions.ADTException;
import model.adt.IADTDictionary;
import model.adt.IADTHeap;
import model.types.IType;
import model.values.IValue;
import exceptions.ExpressionException;

public interface IExpression {
    IValue evaluate(IADTDictionary<String, IValue> symbolTable, IADTHeap heap) throws ExpressionException, ADTException;

    IType typeCheck(IADTDictionary<String, IType> typeTable) throws ExpressionException;
}
