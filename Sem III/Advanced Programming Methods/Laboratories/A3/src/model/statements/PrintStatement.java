package model.statements;

import exceptions.GeneralException;
import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.types.IType;
import model.expressions.IExpression;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws GeneralException {
        state.getOut().add(expression.evaluate(state.getSymbolTable()).toString());
        return null;
    }

    @Override
    public IADTDictionary<String, IType> getType(IADTDictionary<String, IType> typeTable) throws GeneralException {
        expression.getType(typeTable);

        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("print(%s)", expression.toString());
    }
}
