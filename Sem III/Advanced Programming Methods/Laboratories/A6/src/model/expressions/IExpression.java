package model.expressions;

import model.adt.IADTDictionary;
import model.adt.IADTHeap;
import model.values.IValue;
import exceptions.ADTException;
import exceptions.ExpressionException;

public interface IExpression {
    IValue evaluate(IADTDictionary<String, IValue> symbolTable, IADTHeap heap) throws ExpressionException, ADTException;
}
