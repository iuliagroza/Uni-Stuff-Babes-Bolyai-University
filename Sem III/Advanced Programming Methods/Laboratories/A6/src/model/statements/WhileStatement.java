package model.statements;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.StatementException;
import model.expressions.IExpression;
import model.programstate.ProgramState;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.IValue;

public class WhileStatement implements IStatement {
    private final IExpression expression;
    private final IStatement statement;

    public WhileStatement(IExpression expression, IStatement statement) {
        this.expression = expression;
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException, ADTException {
        IValue value = expression.evaluate(state.getSymbolTable(), state.getHeap());
        if (!value.getType().equals(new BoolType())) {
            throw new StatementException(String.format("While Error: %s is not of type bool.", value));
        }

        BoolValue boolValue = (BoolValue) value;
        if (boolValue.getValue()) {
            state.getExecutionStack().push(this);
            state.getExecutionStack().push(statement);
        }

        return null;
    }

    @Override
    public String toString() {
        return String.format("While(%s) {%s}", expression, statement);
    }
}