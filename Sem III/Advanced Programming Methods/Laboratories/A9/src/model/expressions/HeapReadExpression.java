package model.expressions;

import exceptions.ADTException;
import exceptions.ExpressionException;
import model.adt.IADTDictionary;
import model.adt.IADTHeap;
import model.types.IType;
import model.types.ReferenceType;
import model.values.IValue;
import model.values.ReferenceValue;

public class HeapReadExpression implements IExpression {
    private final IExpression expression;

    public HeapReadExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public IValue evaluate(IADTDictionary<String, IValue> symbolTable, IADTHeap heap) throws ExpressionException, ADTException {
        IValue evaluated = expression.evaluate(symbolTable, heap);
        if (!(evaluated instanceof ReferenceValue referenceValue)) {
            throw new ExpressionException(String.format("Heap Read Error: %s not of type Reference.", evaluated));
        }

        return heap.get(referenceValue.getAddress());
    }

    @Override
    public IType typeCheck(IADTDictionary<String, IType> typeTable) throws ExpressionException {
        IType type = expression.typeCheck(typeTable);

        if (type instanceof ReferenceType reference) {
            return reference.getInner();
        } else {
            throw new ExpressionException("Expression Error: ReadHeap argument is not of type Reference.");
        }
    }

    @Override
    public String toString() {
        return String.format("HeapRead(%s)", expression);
    }
}