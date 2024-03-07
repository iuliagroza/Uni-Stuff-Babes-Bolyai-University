package model.programstate;

import model.adt.*;
import model.statements.IStatement;
import model.values.IValue;

import java.io.BufferedReader;
import java.util.Map;

public class ProgramState {
    private final IADTStack<IStatement> executionStack;
    private final IADTDictionary<String, IValue> symbolTable;
    private final IADTList<String> out;
    private final IADTHeap heap;
    private final IADTDictionary<String, BufferedReader> fileTable;

    private int id = 1;

    public ProgramState(IStatement originalProgram) {
        executionStack = new ADTStack<>();
        symbolTable = new ADTDictionary<>();
        out = new ADTList<>();
        heap = new ADTHeap();
        fileTable = new ADTDictionary<>();

        executionStack.push(originalProgram);
    }

    public ProgramState(IADTStack<IStatement> executionStack, IADTDictionary<String, IValue> symTable, IADTList<String> out, IADTHeap heap, IADTDictionary<String, BufferedReader> fileTable) {
        this.executionStack = executionStack;
        this.symbolTable = symTable;
        this.out = out;
        this.heap = heap;
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

    public IADTHeap getHeap() {
        return heap;
    }

    public IADTDictionary<String, BufferedReader> getFileTable() {
        return fileTable;
    }

    public int getId() {
        return this.id;
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

    public String heapToString() {
        StringBuilder heapStringBuilder = new StringBuilder();
        Map<Integer, IValue> map = heap.getContent();

        for (Integer key : map.keySet()) {
            heapStringBuilder.append(key).append(" -> ").append(map.get(key)).append("\n");
        }

        return heapStringBuilder.toString();
    }

    public String fileTableToString() {
        StringBuilder fileTableStringBuilder = new StringBuilder();
        for (String obj : fileTable.keySet())
            fileTableStringBuilder.append(obj).append("\n");
        return fileTableStringBuilder.toString();
    }

    @Override
    public String toString() {
        return String.format("------EXE_STACK------\n%s\n------SYM_TABLE------\n%s\n------OUT------\n%s\n------HEAP_TABLE------\n%s\n------FILE_TABLE------\n%s\n", executionStackToString(), symTableToString(), outToString(), heapToString(), fileTableToString());
    }
}
