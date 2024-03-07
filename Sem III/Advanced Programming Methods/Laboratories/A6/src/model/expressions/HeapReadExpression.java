package model.expressions;

import exceptions.ADTException;
import exceptions.ExpressionException;
import model.adt.IADTDictionary;
import model.adt.IADTHeap;
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
        if (!(evaluated instanceof ReferenceValue)) {
            throw new ExpressionException(String.format("Heap Read Error: %s not of type Reference.", evaluated));
        }

        ReferenceValue referenceValue = (ReferenceValue) evaluated;
        return heap.get(referenceValue.getAddress());
    }

    @Override
    public String toString() {
        return String.format("HeapRead(%s)", expression);
    }
}