package model.expression;

import exceptions.InterpreterException;
import model.type.Type;
import model.utils.MyIDictionary;
import model.utils.MyIHeap;
import model.value.Value;

public class VariableExpression implements IExpression {
    String key;

    public VariableExpression(String key) {
        this.key = key;
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        try {
            return typeEnv.lookUp(key);
        } catch (exceptions.InterpreterException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> table, MyIHeap heap) throws InterpreterException {
        try {
            return table.lookUp(key);
        } catch (exceptions.InterpreterException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public IExpression deepCopy() {
        return new VariableExpression(key);
    }

    @Override
    public String toString() {
        return key;
    }
}
