package repository;

import model.programstate.ProgramState;

import java.io.IOException;

public interface IRepository {
    ProgramState getCurrentProgramState();

    void addProgramState(ProgramState newProgramState);

    void logProgramStateExecution(ProgramState programState) throws IOException;
}
