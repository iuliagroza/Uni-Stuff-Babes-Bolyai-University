package model.statements;

import exceptions.ADTException;
import exceptions.StatementException;
import model.adt.IADTDictionary;
import model.programstate.ProgramState;
import model.expressions.IExpression;
import exceptions.ExpressionException;
import model.types.IType;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ExpressionException, ADTException {
        state.getOut().add(expression.evaluate(state.getSymbolTable(), state.getHeap()).toString());
        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> typeTable) throws StatementException, ExpressionException {
        expression.typeCheck(typeTable);
        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("print(%s)", expression.toString());
    }
}
