package model.expressions;

import exceptions.ADTException;
import model.adt.IADTDictionary;
import model.adt.IADTHeap;
import model.types.BoolType;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;
import model.values.BoolValue;
import exceptions.ExpressionException;

public class RelationalExpression implements IExpression {
    private final IExpression expression1;

    private final IExpression expression2;

    String operator;

    public RelationalExpression(IExpression expression1, IExpression expression2, String operator) {
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.operator = operator;
    }

    @Override
    public IValue evaluate(IADTDictionary<String, IValue> symbolTable, IADTHeap heap) throws ExpressionException, ADTException {
        IValue value1 = expression1.evaluate(symbolTable, heap);
        IValue value2 = expression2.evaluate(symbolTable, heap);

        if (!value1.getType().equals(new IntType())) {
            throw new ExpressionException("Relational Error: The first operand is not an integer.");
        }
        if (!value2.getType().equals(new IntType())) {
            throw new ExpressionException("Relational Error: The second operand is not an integer.");
        }

        int intValue1 = ((IntValue) value1).getValue();
        int intValue2 = ((IntValue) value2).getValue();

        return switch (operator) {
            case ">" -> new BoolValue(intValue1 > intValue2);
            case "<" -> new BoolValue(intValue1 < intValue2);
            case ">=" -> new BoolValue(intValue1 >= intValue2);
            case "<=" -> new BoolValue(intValue1 <= intValue2);
            case "==" -> new BoolValue(intValue1 == intValue2);
            case "!=" -> new BoolValue(intValue1 != intValue2);
            default -> throw new ArithmeticException("Invalid operand!");
        };
    }

    @Override
    public IType typeCheck(IADTDictionary<String, IType> typeTable) throws ExpressionException {
        IType type1, type2;
        type1 = expression1.typeCheck(typeTable);
        type2 = expression2.typeCheck(typeTable);

        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new BoolType();
            } else {
                throw new ExpressionException("Expression Error: The second operand is not an integer.");
            }
        } else {
            throw new ExpressionException("Expression Error: The first operand is not an integer.");
        }
    }

    public String toString() {
        return expression1.toString() + " " + operator + " " + expression2.toString();
    }
}