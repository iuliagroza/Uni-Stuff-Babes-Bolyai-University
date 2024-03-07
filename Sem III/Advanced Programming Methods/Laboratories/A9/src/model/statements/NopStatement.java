package model.statements;

import model.adt.IADTDictionary;
import model.programstate.ProgramState;
import model.types.IType;

public class NopStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> typeTable) {
        return typeTable;
    }

    @Override
    public String toString() {
        return "nop";
    }
}
