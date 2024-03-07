package model.statement;

import exceptions.InterpreterException;
import model.programState.ProgramState;
import model.type.Type;
import model.utils.MyIDictionary;

public class NopStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        return typeEnv;
    }

    @Override
    public IStatement deepCopy() {
        return new NopStatement();
    }

    @Override
    public String toString() {
        return "NopStatement";
    }
}
