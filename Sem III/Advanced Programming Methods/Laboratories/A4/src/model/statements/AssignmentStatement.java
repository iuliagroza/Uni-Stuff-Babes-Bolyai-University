package model.statements;

import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.types.IType;
import model.values.IValue;
import model.expressions.IExpression;
import exceptions.StatementException;
import exceptions.ExpressionException;

public class AssignmentStatement implements IStatement {
    private final String variable;
    private final IExpression expression;

    public AssignmentStatement(String variable, IExpression expression) {
        this.variable = variable;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException {
        IADTDictionary<String, IValue> symbolTable = state.getSymbolTable();

        if (!symbolTable.containsKey(variable)) {
            throw new StatementException(String.format("Assignment Error: Variable %s was not declared before.", variable));
        }

        IType type = symbolTable.get(variable).getType();
        IValue value = expression.evaluate(symbolTable);

        if (!value.getType().equals(type)) {
            throw new StatementException(String.format("Assignment Error: Declared type of variable %s and type of assigned expression %s do not match.", value, type.toString()));
        }

        symbolTable.put(variable, value);

        return null;
    }

    @Override
    public String toString() {
        return String.format("%s=%s", variable, expression);
    }
}
