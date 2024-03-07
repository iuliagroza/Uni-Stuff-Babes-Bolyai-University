package model.expressions;

import model.adt.IADTDictionary;
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
    public IValue evaluate(IADTDictionary<String, IValue> symbolTable) throws ExpressionException {
        IValue value1 = expression1.evaluate(symbolTable);
        IValue value2 = expression2.evaluate(symbolTable);

        if(!value1.getType().equals(new IntType())) {
            throw new ExpressionException("Relational Error: The first operand is not an integer.");
        }
        if(!value2.getType().equals(new IntType())) {
            throw new ExpressionException("Relational Error: The second operand is not an integer.");
        }

        int intValue1 = ((IntValue)value1).getValue();
        int intValue2 = ((IntValue)value2).getValue();

        switch (operator) {
            case ">":
                return new BoolValue(intValue1 > intValue2);
            case "<":
                return new BoolValue(intValue1 < intValue2);
            case ">=":
                return new BoolValue(intValue1 >= intValue2);
            case "<=":
                return new BoolValue(intValue1 <= intValue2);
            case "==":
                return new BoolValue(intValue1 == intValue2);
            case "!=":
                return new BoolValue(intValue1 != intValue2);
            default:
                throw new ArithmeticException("Invalid operand!");
        }
    }

    public String toString() {
        return expression1.toString() + " " + operator + "  " + expression2.toString();
    }
}