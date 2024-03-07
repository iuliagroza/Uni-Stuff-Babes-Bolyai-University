package controller;

import model.adt.ADTList;
import model.adt.IADTDictionary;
import model.adt.IADTStack;
import model.programstate.ProgramState;
import model.statements.IStatement;
import model.types.ReferenceType;
import model.values.IValue;
import model.values.ReferenceValue;
import repository.IRepository;
import exceptions.ADTException;
import exceptions.StatementException;
import exceptions.ExpressionException;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private final IRepository repository;

    private boolean displayFlag;

    public Controller(IRepository repository, boolean displayFlag) {
        this.repository = repository;
        this.displayFlag = displayFlag;
    }

    public IRepository getRepository() {
        return repository;
    }

    public void setDisplayFlag(boolean displayFlag) {
        this.displayFlag = displayFlag;
    }

    public void addProgram(IStatement statement) {
        repository.addProgramState(new ProgramState(statement));
    }

    HashMap<Integer, IValue> safeGarbageCollector(IADTDictionary<String, IValue> symbols, Map<Integer, IValue> heap) {
        HashMap<Integer, IValue> newHeap = new HashMap<>();

        for (IValue val : symbols.getDictionary().values()) {
            if (val instanceof ReferenceValue) {
                int address = ((ReferenceValue) val).getAddress();
                if (heap.containsKey(address)) {
                    newHeap.put(address, heap.get(address));
                }

                if(val.getType() instanceof ReferenceType) {
                    if(heap.containsKey(address)) {
                        IValue value = heap.get(address);
                        while(value instanceof ReferenceValue) {
                            int address2 = ((ReferenceValue) value).getAddress();
                            if(heap.containsKey(address2)) {
                                newHeap.put(address2, heap.get(address2));
                            }
                            value = heap.get(address2);
                        }
                    }
                }
            }
        }
        return newHeap;
    }

    public void executeOneStep(ProgramState programState) throws StatementException, ExpressionException, ADTException, IOException {
        IADTStack<IStatement> executionStack = programState.getExecutionStack();

        if (executionStack.isEmpty()) {
            throw new StatementException("Execution Stack Error: Execution stack is empty.");
        }

        IStatement currentStatement = executionStack.pop();
        currentStatement.execute(programState);

        displayCurrentState(programState);
        repository.logProgramStateExecution(programState);
    }

    public void executeAllSteps() throws StatementException, ExpressionException, ADTException, IOException {
        ProgramState currentProgramState = repository.getCurrentProgramState();
        displayCurrentState(currentProgramState);
        repository.logProgramStateExecution(currentProgramState);

        if (displayFlag) {
            while (!currentProgramState.getExecutionStack().isEmpty()) {
                System.out.println(">>> ");
                Scanner readOption = new Scanner(System.in);
                String option = readOption.next();
                while (!option.equals("step")) {
                    System.out.println("Invalid syntax!");
                    System.out.println(">>> ");
                    option = readOption.next();
                }
                currentProgramState.getHeap().setContent(safeGarbageCollector(currentProgramState.getSymbolTable(), currentProgramState.getHeap().getContent()));
                executeOneStep(currentProgramState);
            }
        } else {
            while (!currentProgramState.getExecutionStack().isEmpty()) {
                currentProgramState.getHeap().setContent(safeGarbageCollector(currentProgramState.getSymbolTable(), currentProgramState.getHeap().getContent()));
                executeOneStep(currentProgramState);
            }
        }
    }

    public void displayCurrentState(ProgramState programState) {
        System.out.println(programState.toString() + "\n");
    }
}
