package model.statements;

import exceptions.GeneralException;
import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.types.IType;
import model.types.BoolType;
import model.values.IValue;
import model.values.BoolValue;
import model.expressions.IExpression;

public class IfStatement implements IStatement {
    private final IExpression expression;

    private final IStatement thenStatement;

    private final IStatement elseStatement;

    public IfStatement(IExpression expression, IStatement thenStatement, IStatement elseStatement) {
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws GeneralException {
        IValue value = expression.evaluate(state.getSymbolTable());

        if (!value.getType().equals(new BoolType())) {
            throw new GeneralException(String.format("Conditional Error: Condition %s is not of type bool.", value));
        }

        BoolValue condition = (BoolValue) value;
        if (condition.getValue()) {
            state.getExecutionStack().push(thenStatement);
        } else {
            state.getExecutionStack().push(elseStatement);
        }
        return null;
    }

    @Override
    public IADTDictionary<String, IType> getType(IADTDictionary<String, IType> typeTable) throws GeneralException {
        if (!expression.getType(typeTable).equals(new BoolType())) {
            throw new GeneralException("Conditional Error: Condition is not of type bool.");
        }

        thenStatement.getType(typeTable.copy());
        elseStatement.getType(typeTable.copy());

        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("if(%s) then(%s) else(%s)", expression.toString(), thenStatement.toString(), elseStatement.toString());
    }
}
