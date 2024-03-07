package repository;

import model.programstate.ProgramState;

import java.util.List;

public interface IRepository {
    ProgramState getCurrentProgramState();

    void addProgramState(ProgramState newProgramState);
}
