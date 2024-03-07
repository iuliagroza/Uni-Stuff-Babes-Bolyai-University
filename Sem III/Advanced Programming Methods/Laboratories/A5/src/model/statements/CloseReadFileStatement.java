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
import java.io.IOException;

public class CloseReadFileStatement implements IStatement {
    private final IExpression expression;

    public CloseReadFileStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException, ADTException {
        IValue value = expression.evaluate(state.getSymbolTable(), state.getHeap());
        if (!value.getType().equals(new StringType())) {
            throw new StatementException(String.format("Close Read File Error: %s is not of type string.", expression));
        }

        StringValue fileName = (StringValue) value;
        IADTDictionary<String, BufferedReader> fileTable = state.getFileTable();
        if (!fileTable.containsKey(fileName.getValue())) {
            throw new StatementException(String.format("Close Read File Error: Variable %s was not declared before.", value));
        }

        BufferedReader bufferedReader = fileTable.get(fileName.getValue());
        try {
            bufferedReader.close();
        } catch (IOException e) {
            throw new StatementException(String.format("Close Read File Error: File %s could not be closed.", value));
        }

        fileTable.remove(fileName.getValue());

        return null;
    }

    @Override
    public String toString() {
        return String.format("CloseReadFile(%s)", expression);
    }

}
