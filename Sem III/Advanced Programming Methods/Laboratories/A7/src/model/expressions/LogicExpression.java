package model.expressions;

import exceptions.ADTException;
import exceptions.ExpressionException;
import model.adt.IADTDictionary;
import model.adt.IADTHeap;
import model.types.BoolType;
import model.types.IType;
import model.values.IValue;
import model.values.BoolValue;

public class LogicExpression implements IExpression {
    private final IExpression expression1;

    private final IExpression expression2;

    String operator;

    public LogicExpression(IExpression expression1, IExpression expression2, String operator) {
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.operator = operator;
    }

    @Override
    public IValue evaluate(IADTDictionary<String, IValue> symbolTable, IADTHeap heap) throws ExpressionException, ADTException {
        IValue value1 = expression1.evaluate(symbolTable, heap);
        IValue value2 = expression2.evaluate(symbolTable, heap);

        if (!value1.getType().equals(new BoolType())) {
            throw new ExpressionException("Logic Error: The first operand is not a boolean.");
        }
        if (!value2.getType().equals(new BoolType())) {
            throw new ExpressionException("Logic Error: The second operand is not a boolean.");
        }

        BoolValue bool1 = (BoolValue) value1;
        BoolValue bool2 = (BoolValue) value2;

        return switch (operator) {
            case "and" -> new BoolValue(bool1.getValue() && bool2.getValue());
            case "or" -> new BoolValue(bool1.getValue() || bool2.getValue());
            default -> throw new ExpressionException("Logic Error: Invalid boolean operator.");
        };
    }

    @Override
    public IType typeCheck(IADTDictionary<String, IType> typeTable) throws ExpressionException {
        IType type1, type2;
        type1 = expression1.typeCheck(typeTable);
        type2 = expression2.typeCheck(typeTable);

        if (type1.equals(new BoolType())) {
            if (type2.equals(new BoolType())) {
                return new BoolType();
            } else {
                throw new ExpressionException("Expression Error: The second operand is not of type bool.");
            }
        } else {
            throw new ExpressionException("Expression Error: The first operand is not of type bool.");
        }
    }

    public String toString() {
        return expression1.toString() + " " + operator + "  " + expression2.toString();
    }
}
