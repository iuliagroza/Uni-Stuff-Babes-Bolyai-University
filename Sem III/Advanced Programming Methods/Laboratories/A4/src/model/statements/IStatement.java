package model.statements;

import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.types.IType;
import exceptions.StatementException;
import exceptions.ExpressionException;

public interface IStatement {
    ProgramState execute(ProgramState state) throws StatementException, ExpressionException;
}
