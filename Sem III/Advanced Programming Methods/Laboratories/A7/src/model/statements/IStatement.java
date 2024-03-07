package model.statements;

import exceptions.ADTException;
import model.adt.IADTDictionary;
import model.programstate.ProgramState;
import exceptions.StatementException;
import exceptions.ExpressionException;
import model.types.IType;

public interface IStatement {
    ProgramState execute(ProgramState state) throws StatementException, ExpressionException, ADTException;

    IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> typeTable) throws StatementException, ExpressionException;
}
