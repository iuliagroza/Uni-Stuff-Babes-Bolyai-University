package model.statements;

import exceptions.ADTException;
import model.programstate.ProgramState;
import exceptions.StatementException;
import exceptions.ExpressionException;

public interface IStatement {
    ProgramState execute(ProgramState state) throws StatementException, ExpressionException, ADTException;
}
