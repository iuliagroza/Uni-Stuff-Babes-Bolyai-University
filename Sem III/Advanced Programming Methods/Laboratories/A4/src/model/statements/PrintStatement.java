package model.statements;

import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.types.IType;
import model.expressions.IExpression;
import exceptions.ExpressionException;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ExpressionException {
        state.getOut().add(expression.evaluate(state.getSymbolTable()).toString());
        return null;
    }

    @Override
    public String toString() {
        return String.format("print(%s)", expression.toString());
    }
}
