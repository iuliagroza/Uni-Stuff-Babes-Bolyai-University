package model.statements;

import model.adt.ADTStack;
import model.programstate.ProgramState;

public class ForkStatement implements IStatement {
    private final IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        ADTStack<IStatement> newExecutionStack = new ADTStack<>();
        newExecutionStack.push(statement);
        return new ProgramState(newExecutionStack, state.getSymbolTable().copy(),
                state.getOut(), state.getHeap(), state.getFileTable());
    }

    @Override
    public String toString() {
        return String.format("fork(%s)", statement);
    }
}