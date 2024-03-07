package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.ADTStack;
import model.adt.IADTDictionary;
import model.adt.IADTStack;
import model.programstate.ProgramState;
import model.types.IType;

public class ForkStatement implements IStatement {
    private final IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> typeTable) throws StatementException, ExpressionException {
        statement.typeCheck(typeTable.copy());
        return typeTable;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        IADTStack<IStatement> newExeStack = new ADTStack<>();
        newExeStack.push(statement);

        return new ProgramState(newExeStack, state.getSymbolTable().copy(),
                state.getOut(), state.getHeap(), state.getFileTable());
    }

    @Override
    public String toString() {
        return String.format("Fork(%s)", statement);
    }
}