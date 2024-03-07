package model.statements;

import exceptions.GeneralException;
import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.types.IType;
import model.values.IValue;
import model.expressions.IExpression;

public class AssignmentStatement implements IStatement {
    private final String variable;
    private final IExpression expression;

    public AssignmentStatement(String variable, IExpression expression) {
        this.variable = variable;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws GeneralException {
        IADTDictionary<String, IValue> symbolTable = state.getSymbolTable();
        IType type = symbolTable.get(variable).getType();
        IValue value = expression.evaluate(symbolTable);

        if (!value.getType().equals(type)) {
            throw new GeneralException(String.format("Assignment Error: Declared type of variable %s and type of assigned expression %s do not match.", value, type.toString()));
        }
        if (!symbolTable.containsKey(variable)) {
            throw new GeneralException(String.format("Assignment Error: Variable %s was not declared before.", variable));
        }

        symbolTable.put(variable, value);

        return null;
    }

    @Override
    public IADTDictionary<String, IType> getType(IADTDictionary<String, IType> typeTable) throws GeneralException {
        if (!typeTable.get(variable).equals(expression.getType(typeTable))) {
            throw new GeneralException("Assignment Error: Right hand side and left hand side have different types.");
        }

        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("%s=%s", variable, expression);
    }
}
