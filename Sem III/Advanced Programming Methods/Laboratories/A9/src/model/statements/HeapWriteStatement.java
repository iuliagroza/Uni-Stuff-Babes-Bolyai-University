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

public class HeapWriteStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;

    public HeapWriteStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException, ADTException {
        IADTDictionary<String, IValue> symbolTable = state.getSymbolTable();
        IADTHeap heap = state.getHeap();
        if (!symbolTable.containsKey(variableName)) {
            throw new StatementException(String.format("Heap Write Error: %s is not defined.", variableName));
        }

        IValue variableValue = symbolTable.get(variableName);
        if (!(variableValue instanceof ReferenceValue)) {
            throw new StatementException(String.format("Heap Write Error: %s is not of type Reference.", variableValue));
        }

        ReferenceValue referenceValue = (ReferenceValue) variableValue;
        IValue evaluated = expression.evaluate(symbolTable, heap);
        if (!evaluated.getType().equals(referenceValue.getLocationType())) {
            throw new StatementException(String.format("Heap Write Error: %s is not of type %s.", evaluated, referenceValue.getLocationType()));
        }

        heap.update(referenceValue.getAddress(), evaluated);
        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> typeTable) throws StatementException, ExpressionException {
        if (typeTable.get(variableName).equals(new ReferenceType(expression.typeCheck(typeTable)))) {
            return typeTable;
        }

        throw new StatementException("Heap Write Error: Variable and expression types are incompatible.");
    }

    @Override
    public String toString() {
        return String.format("WriteHeap{%s, %s}", variableName, expression);
    }
}