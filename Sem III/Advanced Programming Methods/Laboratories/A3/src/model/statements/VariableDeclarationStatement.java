package model.statements;

import exceptions.GeneralException;
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
    public ProgramState execute(ProgramState state) throws GeneralException {
        IADTDictionary<String, IValue> symbolTable = state.getSymbolTable();

        if (symbolTable.containsKey(name)) {
            throw new GeneralException(String.format("Variable Declaration Error: Variable %s is already defined.", name));
        }

        symbolTable.put(name, type.getDefault());

        return null;
    }

    @Override
    public IADTDictionary<String, IType> getType(IADTDictionary<String, IType> typeTable) {
        typeTable.put(name, type);
        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("%s %s", type.toString(), name);
    }
}
