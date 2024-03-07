package model.expressions;

import exceptions.GeneralException;
import model.adt.IADTDictionary;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

public class ArithmeticExpression implements IExpression {
    private final IExpression expression1;

    private final IExpression expression2;

    char operator;

    public ArithmeticExpression(IExpression expression1, IExpression expression2, char operator) {
        this.operator = operator;
        this.expression1 = expression1;
        this.expression2 = expression2;
    }

    @Override
    public IValue evaluate(IADTDictionary<String, IValue> symbolTable) throws GeneralException {
        IValue value1 = expression1.evaluate(symbolTable);
        IValue value2 = expression2.evaluate(symbolTable);

        if (!value1.getType().equals(new IntType())) {
            throw new GeneralException("Arithmetic Error: The first operand is not an integer.");
        }
        if (!value2.getType().equals(new IntType())) {
            throw new GeneralException("Arithmetic Error: The second operand is not an integer.");
        }

        IntValue int1 = (IntValue) value1;
        IntValue int2 = (IntValue) value2;

        switch (operator) {
            case '+':
                return new IntValue(int1.getValue() + int2.getValue());
            case '-':
                return new IntValue(int1.getValue() - int2.getValue());
            case '*':
                return new IntValue(int1.getValue() * int2.getValue());
            case '/':
                if (int2.getValue() == 0) {
                    throw new GeneralException("Arithmetic Error: Division by zero.");
                }
                return new IntValue(int1.getValue() / int2.getValue());
            default:
                throw new GeneralException("Arithmetic Error: Invalid operator.");
        }
    }

    @Override
    public IType getType(IADTDictionary<String, IType> typeTable) throws GeneralException {
        IType type1 = expression1.getType(typeTable);
        IType type2 = expression2.getType(typeTable);

        if (!type1.equals(new IntType())) {
            throw new GeneralException("Arithmetic Error: The first operand is not an integer.");
        }
        if (!type2.equals(new IntType())) {
            throw new GeneralException("Arithmetic Error: The second operand is not an integer.");
        }

        return new IntType();
    }

    private IntValue getValue(IExpression expression, IADTDictionary<String, IValue> symbolTable) throws GeneralException {
        IValue value = expression.evaluate(symbolTable);

        if (!(value instanceof IntValue)) {
            throw new GeneralException(String.format("Arithmetic Error: %s is not of type IntType.", value.toString()));
        }

        return (IntValue) value;
    }

    public String toString() {
        return expression1.toString() + operator + expression2.toString();
    }
}
