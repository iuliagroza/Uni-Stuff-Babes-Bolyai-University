package model.statements;

import model.programstate.ProgramState;
import model.adt.IADTDictionary;
import model.types.IType;
import exceptions.GeneralException;

public interface IStatement {
    ProgramState execute(ProgramState state) throws GeneralException;

    IADTDictionary<String, IType> getType(IADTDictionary<String, IType> typeTable) throws GeneralException;
}
