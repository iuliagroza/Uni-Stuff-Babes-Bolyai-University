package repository;

import model.programstate.ProgramState;

import java.util.LinkedList;
import java.util.List;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.FileWriter;

public class Repository implements IRepository {
    private List<ProgramState> programStates;

    private final String logFilePath;

    public Repository(String logFilePath) {
        programStates = new LinkedList<>();
        this.logFilePath = logFilePath;
    }

    @Override
    public List<ProgramState> getProgramStates() {
        return this.programStates;
    }

    @Override
    public void setProgramStates(List<ProgramState> newProgramStates) {
        programStates = newProgramStates;
    }

    @Override
    public void addProgramState(ProgramState newProgramState) {
        programStates.add(newProgramState);
    }

    @Override
    public void logProgramStateExecution(ProgramState programState) throws IOException {
        PrintWriter logFile;
        logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
        logFile.println(programState.toString());
        logFile.close();
    }
}
