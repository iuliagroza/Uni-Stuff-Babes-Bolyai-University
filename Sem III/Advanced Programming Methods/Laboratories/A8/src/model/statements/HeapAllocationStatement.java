package model.statements;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.IADTDictionary;
import model.adt.IADTHeap;
import model.expressions.IExpression;
import model.programstate.ProgramState;
import model.types.IType;
import model.types.ReferenceType;
import model.values.IValue;
import model.values.ReferenceValue;

public class HeapAllocationStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;

    public HeapAllocationStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException, ADTException {
        IADTDictionary<String, IValue> symbolTable = state.getSymbolTable();
        IADTHeap heap = state.getHeap();

        if (!symbolTable.containsKey(variableName)) {
            throw new StatementException(String.format("Heap Allocation Error: %s is not defined.", variableName));
        }

        IValue variableValue = symbolTable.get(variableName);
        if (!(variableValue.getType() instanceof ReferenceType)) {
            throw new StatementException(String.format("Heap Allocation Error: %s is not of type Reference.", variableName));
        }

        IValue evaluated = expression.evaluate(symbolTable, heap);
        IType locationType = ((ReferenceValue)variableValue).getLocationType();
        if (!locationType.equals(evaluated.getType())) {
            throw new StatementException(String.format("Heap Allocation Error: %s is not of type %s.", variableName, evaluated.getType()));
        }

        Integer newPosition = heap.add(evaluated);
        symbolTable.put(variableName, new ReferenceValue(newPosition, locationType));

        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> typeTable) throws StatementException, ExpressionException {
        IType typeVariable = typeTable.get(variableName);
        IType typeExpression = expression.typeCheck(typeTable);

        if (!typeVariable.equals(new ReferenceType(typeExpression))) {
            throw new StatementException("Heap Allocation Error: Variable and expression types are not compatible.");
        }

        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("New(%s, %s)", variableName, expression);
    }
}