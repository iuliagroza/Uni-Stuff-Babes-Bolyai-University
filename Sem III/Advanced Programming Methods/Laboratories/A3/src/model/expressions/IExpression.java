package model.expressions;

import model.adt.IADTDictionary;
import model.types.IType;
import model.values.IValue;
import exceptions.GeneralException;

public interface IExpression {
    IValue evaluate(IADTDictionary<String, IValue> symbolTable) throws GeneralException;

    IType getType(IADTDictionary<String, IType> typeTable) throws GeneralException;
}
