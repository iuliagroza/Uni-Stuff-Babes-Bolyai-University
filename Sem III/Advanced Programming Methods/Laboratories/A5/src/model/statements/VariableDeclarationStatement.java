package model.statements;

import exceptions.StatementException;
import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.types.IType;
import model.values.IValue;

public class VariableDeclarationStatement implements IStatement {
    private final String name;
    private final IType type;

    public VariableDeclarationStatement(String name, IType type) {
        this.name = name;
        this.type = type;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        IADTDictionary<String, IValue> symbolTable = state.getSymbolTable();

        if (symbolTable.containsKey(name)) {
            throw new StatementException(String.format("Variable Declaration Error: Variable %s is already defined.", name));
        }

        symbolTable.put(name, type.getDefault());

        return null;
    }

    @Override
    public String toString() {
        return String.format("%s %s", type.toString(), name);
    }
}
