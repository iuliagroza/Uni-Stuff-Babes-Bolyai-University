package controller;

import model.adt.IADTStack;
import model.programstate.ProgramState;
import model.statements.IStatement;
import repository.IRepository;
import exceptions.ADTException;
import exceptions.StatementException;
import exceptions.ExpressionException;

import java.io.IOException;
import java.util.Scanner;

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

    public void executeOneStep(ProgramState programState) throws StatementException, ExpressionException, ADTException, IOException {
        IADTStack<IStatement> executionStack = programState.getExecutionStack();

        if(executionStack.isEmpty()) {
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

        if(displayFlag) {
            while (!currentProgramState.getExecutionStack().isEmpty()) {
                System.out.println(">>> ");
                Scanner readOption = new Scanner(System.in);
                String option = readOption.next();
                while (!option.equals("step")) {
                    System.out.println("Invalid syntax!");
                    System.out.println(">>> ");
                    option = readOption.next();
                }
                executeOneStep(currentProgramState);
            }
        } else {
            while (!currentProgramState.getExecutionStack().isEmpty()) {
                executeOneStep(currentProgramState);
            }
        }
    }

    public void displayCurrentState(ProgramState programState) {
        System.out.println(programState.toString() + "\n");
    }
}
