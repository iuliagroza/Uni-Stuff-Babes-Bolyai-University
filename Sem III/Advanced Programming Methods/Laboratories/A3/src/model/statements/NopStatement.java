package model.statements;

import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.types.IType;

public class NopStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public IADTDictionary<String, IType> getType(IADTDictionary<String, IType> typeTable) {
        return typeTable;
    }

    @Override
    public String toString() {
        return "nop";
    }
}
