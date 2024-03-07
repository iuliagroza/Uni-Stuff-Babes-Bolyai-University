package controller;

import exceptions.GeneralException;
import model.adt.IADTStack;
import model.programstate.ProgramState;
import model.statements.IStatement;
import repository.IRepository;
import repository.Repository;

public class Controller {
    private final IRepository repository;

    private final boolean displayFlag;

    public Controller() {
        repository = new Repository();
        this.displayFlag = false;
    }

    public Controller(boolean displayFlag) {
        repository = new Repository();
        this.displayFlag = displayFlag;
    }

    public IRepository getRepository() {
        return repository;
    }

    public void addProgram(IStatement statement) {
        repository.addProgramState(new ProgramState(statement));
    }

    public void executeOneStep(ProgramState programState) throws GeneralException {
        IADTStack<IStatement> executionStack = programState.getExecutionStack();

        if(executionStack.isEmpty()) {
            throw new GeneralException("Execution Stack Error: Execution stack is empty.");
        }

        IStatement currentStatement = executionStack.pop();
        currentStatement.execute(programState);

        if(displayFlag) {
            displayCurrentState(programState);
        }
    }

    public void executeAllSteps() throws GeneralException {
        ProgramState currentProgramState = repository.getCurrentProgramState();

        if (displayFlag) {
            displayCurrentState(currentProgramState);
        }

        while (!currentProgramState.getExecutionStack().isEmpty()) {
            executeOneStep(currentProgramState);
        }
    }

    public void displayCurrentState(ProgramState programState) {
        System.out.println(programState.toString() + "\n");
    }
}
