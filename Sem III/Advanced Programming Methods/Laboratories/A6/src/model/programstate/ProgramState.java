package model.programstate;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.*;
import model.statements.IStatement;
import model.values.IValue;

import java.io.BufferedReader;
import java.util.Map;
import java.util.Random;
import java.util.TreeSet;

public class ProgramState {
    private final IADTStack<IStatement> executionStack;
    private final IADTDictionary<String, IValue> symbolTable;
    private final IADTList<String> out;
    private final IADTHeap heap;
    private final IADTDictionary<String, BufferedReader> fileTable;
    public final Integer id;
    private static int lastId = 0;

    public ProgramState(IStatement originalProgram) {
        executionStack = new ADTStack<>();
        symbolTable = new ADTDictionary<>();
        out = new ADTList<>();
        heap = new ADTHeap();
        fileTable = new ADTDictionary<>();
        id = setId();

        executionStack.push(originalProgram);
    }

    public ProgramState(IADTStack<IStatement> executionStack, IADTDictionary<String, IValue> symTable, IADTList<String> out, IADTHeap heap, IADTDictionary<String, BufferedReader> fileTable) {
        this.executionStack = executionStack;
        this.symbolTable = symTable;
        this.out = out;
        this.heap = heap;
        this.fileTable = fileTable;
        id = setId();
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

    public synchronized int setId() {
        lastId++;
        return lastId;
    }

    public ProgramState executeOneStep() throws StatementException, ADTException, ExpressionException {
        if (executionStack.isEmpty()) {
            throw new StatementException("Execution Stack Error: Execution stack is empty.");
        }

        IStatement currentStatement = executionStack.pop();
        return currentStatement.execute(this);
    }

    public boolean isNotCompleted() {
        return !executionStack.isEmpty();
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
        return String.format("------ID------\n%d\n------EXE_STACK------\n%s\n------SYM_TABLE------\n%s\n------OUT------\n%s\n------HEAP_TABLE------\n%s\n------FILE_TABLE------\n%s\n", id, executionStackToString(), symTableToString(), outToString(), heapToString(), fileTableToString());
    }
}
