package repository;

import model.programstate.ProgramState;

import java.util.LinkedList;
import java.util.List;

public class Repository implements IRepository {
    private final List<ProgramState> programStates;

    private final int currentPosition;

    public Repository() {
        programStates = new LinkedList<>();
        currentPosition = 0;
    }

    @Override
    public ProgramState getCurrentProgramState() {
        return programStates.get(currentPosition);
    }

    @Override
    public void addProgramState(ProgramState newProgramState) {
        programStates.add(newProgramState);
    }
}
