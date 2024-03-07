package model.statements;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.IADTDictionary;
import model.expressions.IExpression;
import model.programstate.ProgramState;
import model.types.StringType;
import model.values.IValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenReadFileStatement implements IStatement {
    private final IExpression expression;

    public OpenReadFileStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException, ADTException {
        IValue value = expression.evaluate(state.getSymbolTable(), state.getHeap());

        if (!value.getType().equals(new StringType())) {
            throw new StatementException(String.format("Open Read File Error: %s is not of type string.", expression));
        }

        StringValue fileName = (StringValue) value;

        IADTDictionary<String, BufferedReader> fileTable = state.getFileTable();
        if (fileTable.containsKey(fileName.getValue())) {
            throw new StatementException(String.format("Open Read File Error: File %s is already open.", fileName));
        }

        BufferedReader bufferedReader;
        try {
            bufferedReader = new BufferedReader(new FileReader(fileName.getValue()));
        } catch (IOException e) {
            throw new StatementException(String.format("Open Read File Error: File %s could not be open.", fileName));
        }

        fileTable.put(fileName.getValue(), bufferedReader);

        return null;
    }

    @Override
    public String toString() {
        return String.format("OpenReadFile(%s)", expression);
    }
}
