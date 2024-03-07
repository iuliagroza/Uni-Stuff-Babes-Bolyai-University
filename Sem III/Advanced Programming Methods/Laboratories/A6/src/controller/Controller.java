package controller;

import model.adt.IADTDictionary;
import model.adt.IADTList;
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
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private final IRepository repository;

    private ExecutorService executor;

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

    List<ProgramState> removeCompletedPrograms(List<ProgramState> programStates) {
        List<ProgramState> toReturn = programStates.stream().filter(ProgramState::isNotCompleted).collect(Collectors.toList());

        if (toReturn.isEmpty() && !programStates.isEmpty()) {
            toReturn.add(programStates.get(0));
        }

        return toReturn;
    }

    /*HashMap<Integer, IValue> safeGarbageCollector(IADTDictionary<String, IValue> symbols, Map<Integer, IValue> heap) {
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
    }*/

    public List<Integer> getAddrFromSymTable(Collection<IValue> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof ReferenceValue)
                .map(v -> {ReferenceValue v1 = (ReferenceValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public List<Integer> getAddrFromHeap(Collection<IValue> heapValues) {
        return heapValues.stream()
                .filter(v -> v instanceof ReferenceValue)
                .map(v -> {ReferenceValue v1 = (ReferenceValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public Map<Integer, IValue> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapAddr, Map<Integer, IValue> heap) {
        return heap.entrySet().stream()
                .filter(e -> ( symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public void conservativeGarbageCollector(List<ProgramState> programStates) {
        List<Integer> symTableAddresses = Objects.requireNonNull(programStates.stream()
                        .map(p -> getAddrFromSymTable(p.getSymbolTable().getDictionary().values()))
                        .map(Collection::stream)
                        .reduce(Stream::concat).orElse(null))
                .collect(Collectors.toList());
        programStates.forEach(p -> {
            p.getHeap().setContent((HashMap<Integer, IValue>) safeGarbageCollector(symTableAddresses, getAddrFromHeap(p.getHeap().getContent().values()), p.getHeap().getContent()));
        });
    }

    public void executeOneStepForAllPrograms(List<ProgramState> programStates) throws InterruptedException {
        programStates.forEach(programState -> {
            try {
                repository.logProgramStateExecution(programState);
                displayCurrentState(programState);
            } catch (IOException e) {
                System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
            }
        });

        List<Callable<ProgramState>> callList = programStates.stream()
                .map((ProgramState p) -> (Callable<ProgramState>) (p::executeOneStep))
                .collect(Collectors.toList());

        List<ProgramState> newProgramList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (ExecutionException | InterruptedException e) {
                        System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
                    }
                    return null;
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList());

        programStates.addAll(newProgramList);

        programStates.forEach(programState -> {
            try {
                repository.logProgramStateExecution(programState);
            } catch (IOException e) {
                System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
            }
        });
        repository.setProgramStates(programStates);
    }

    public void allStep() throws InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        List<ProgramState> programStates = removeCompletedPrograms(repository.getProgramStates());
        while (programStates.size() > 0) {
            conservativeGarbageCollector(programStates);
            executeOneStepForAllPrograms(programStates);
            programStates = removeCompletedPrograms(repository.getProgramStates());
        }
        executor.shutdownNow();
        repository.setProgramStates(programStates);
    }

    public void displayCurrentState(ProgramState programState) {
        System.out.println(programState.toString() + "\n");
    }
}
