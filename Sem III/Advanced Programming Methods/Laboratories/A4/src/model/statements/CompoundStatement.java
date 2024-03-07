package model.statements;

import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.adt.IADTStack;
import model.types.IType;
import exceptions.StatementException;
import exceptions.ExpressionException;

public class CompoundStatement implements IStatement {
    private final IStatement first;
    private final IStatement second;

    public CompoundStatement(IStatement first, IStatement second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        IADTStack<IStatement> stack = state.getExecutionStack();
        stack.push(second);
        stack.push(first);

        return null;
    }

    @Override
    public String toString() {
        return String.format("%s;%s", first, second);
    }
}
