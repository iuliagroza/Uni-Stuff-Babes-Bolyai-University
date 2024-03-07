package model.programstate;

import model.adt.*;
import model.statements.IStatement;
import model.values.IValue;

import java.io.BufferedReader;

public class ProgramState {
    private final IADTStack<IStatement> executionStack;
    private final IADTDictionary<String, IValue> symbolTable;
    private final IADTList<String> out;

    private final IADTDictionary<String, BufferedReader> fileTable;

    public ProgramState(IStatement originalProgram) {
        executionStack = new ADTStack<>();
        symbolTable = new ADTDictionary<>();
        out = new ADTList<>();
        fileTable = new ADTDictionary<>();

        executionStack.push(originalProgram);
    }

    public ProgramState(IADTStack<IStatement> executionStack, IADTDictionary<String, IValue> symTable, IADTList<String> out, IADTDictionary<String, BufferedReader> fileTable) {
        this.executionStack = executionStack;
        this.symbolTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
    }

    public IADTStack<IStatement> getExecutionStack() {
        return executionStack;
    }

    public IADTDictionary<String, IValue> getSymbolTable() {
        return symbolTable;
    }

    public IADTList<String> getOut() {
        return out;
    }

    public IADTDictionary<String, BufferedReader> getFileTable() {
        return fileTable;
    }

    public String executionStackToString() {
        StringBuilder executionStackStringBuilder = new StringBuilder();

        for (IStatement statement : executionStack) {
            executionStackStringBuilder.append(statement.toString()).append("\n");
        }

        return executionStackStringBuilder.toString();
    }

    public String symTableToString() {
        StringBuilder symbolTableStringBuilder = new StringBuilder();

        for (String key : symbolTable.keySet()) {
            symbolTableStringBuilder.append(String.format("%s -> %s\n", key, symbolTable.get(key).toString()));
        }

        return symbolTableStringBuilder.toString();
    }

    public String outToString() {
        StringBuilder outStringBuilder = new StringBuilder();

        for (String object : out) {
            outStringBuilder.append(object).append("\n");
        }

        return outStringBuilder.toString();
    }

    public String fileTableToString() {
        StringBuilder fileTableStringBuilder = new StringBuilder();
        for (String obj : fileTable.keySet())
            fileTableStringBuilder.append(obj).append("\n");
        return fileTableStringBuilder.toString();
    }

    @Override
    public String toString() {
        return String.format("------EXE_STACK------\n%s\n------SYM_TABLE------\n%s\n------OUT------\n%s\n------FILE_TABLE------\n%s\n", executionStackToString(), symTableToString(), outToString(), fileTableToString());
    }
}
