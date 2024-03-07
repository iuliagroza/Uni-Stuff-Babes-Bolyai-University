package repository;

import model.programstate.ProgramState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    List<ProgramState> getProgramStates();

    void setProgramStates(List<ProgramState> newList);

    ProgramState getCurrentProgramState();

    void addProgramState(ProgramState newProgramState);

    void logProgramStateExecution(ProgramState programState) throws IOException;
}
