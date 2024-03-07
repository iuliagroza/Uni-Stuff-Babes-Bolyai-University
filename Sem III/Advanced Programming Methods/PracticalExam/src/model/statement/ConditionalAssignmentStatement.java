package model.statement;

import exceptions.InterpreterException;
import model.expression.IExpression;
import model.expression.VariableExpression;
import model.programState.ProgramState;
import model.type.BoolType;
import model.type.Type;
import model.utils.MyIDictionary;
import model.utils.MyIStack;

public class ConditionalAssignmentStatement implements IStatement{
    private final String variable;
    private final IExpression expression1;
    private final IExpression expression2;
    private final IExpression expression3;

    public ConditionalAssignmentStatement(String variable, IExpression expression1, IExpression expression2, IExpression expression3) {
        this.variable = variable;
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.expression3 = expression3;
    }
    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        MyIStack<IStatement> exeStack = state.getExeStack();
        IStatement converted = new IfStatement(expression1, new AssignStatement(variable, expression2), new AssignStatement(variable, expression3));
        exeStack.push(converted);
        state.setExeStack(exeStack);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        Type variableType = new VariableExpression(variable).typeCheck(typeEnv);
        Type type1 = expression1.typeCheck(typeEnv);
        Type type2 = expression2.typeCheck(typeEnv);
        Type type3 = expression3.typeCheck(typeEnv);
        if (type1.equals(new BoolType()) && type2.equals(variableType) && type3.equals(variableType))
            return typeEnv;
        else
            throw new InterpreterException("The conditional assignment is invalid!");
    }

    @Override
    public IStatement deepCopy() {
        return new ConditionalAssignmentStatement(variable, expression1.deepCopy(), expression2.deepCopy(), expression3.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("%s=(%s)? %s: %s", variable, expression1, expression2, expression3);
    }
}