package model.statements;

import exceptions.ADTException;
import model.adt.IADTDictionary;
import model.types.IType;
import model.types.IntType;
import model.types.StringType;
import model.values.IValue;
import model.values.IntValue;
import model.values.StringValue;
import model.expressions.IExpression;
import model.programstate.ProgramState;
import exceptions.StatementException;
import exceptions.ExpressionException;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement {
    private final IExpression expression;
    private final String varName;

    public ReadFileStatement(IExpression expression, String varName) {
        this.expression = expression;
        this.varName = varName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, ExpressionException, ADTException {
        IADTDictionary<String, IValue> symbolTable = state.getSymbolTable();
        IADTDictionary<String, BufferedReader> fileTable = state.getFileTable();

        if (!symbolTable.containsKey(varName)) {
            throw new StatementException(String.format("Read File Error: Variable %s was not declared before.", varName));
        }

        IValue value = symbolTable.get(varName);
        if (!value.getType().equals(new IntType())) {
            throw new StatementException(String.format("Read File Error: %s is not of type integer.", value));
        }

        value = expression.evaluate(symbolTable, state.getHeap());
        if (!value.getType().equals(new StringType())) {
            throw new StatementException(String.format("Read File Error: %s is not of type string.", value));
        }

        StringValue castValue = (StringValue) value;
        if (!fileTable.containsKey(castValue.getValue())) {
            throw new StatementException(String.format("Read File Error: No file %s found.", castValue));
        }

        BufferedReader bufferedReader = fileTable.get(castValue.getValue());
        try {
            String line = bufferedReader.readLine();
            if (line == null) {
                line = "0";
            }

            symbolTable.put(varName, new IntValue(Integer.parseInt(line)));
        } catch (IOException e) {
            throw new StatementException(String.format("Read File Error: Could not read from file %s.", castValue));
        }

        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> typeTable) throws StatementException, ExpressionException {
        if (!expression.typeCheck(typeTable).equals(new StringType())) {
            throw new StatementException("Read File Error: ReadFile() requires a string expression.");
        }
        if (!typeTable.get(varName).equals(new IntType())) {
            throw new StatementException("Read File Error: ReadFile() requires an int as variable.");
        }

        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("ReadFile(%s, %s)", expression, varName);
    }
}
