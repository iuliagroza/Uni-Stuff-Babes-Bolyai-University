package view;

import controller.Controller;
import exceptions.GeneralException;
import model.expressions.ArithmeticExpression;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IntValue;
import model.expressions.ValueExpression;
import model.expressions.VariableExpression;

public class View {
    public static void main(String[] args) {
        try {
            runProgram3();
        } catch(GeneralException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void runProgram1() throws GeneralException {
        IStatement statement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));

        runStatement(statement);
    }

    private static void runProgram2() throws GeneralException {
        IStatement statement = new CompoundStatement(new VariableDeclarationStatement("a",new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b",new IntType()),
                        new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression(new ValueExpression(new IntValue(2)),new
                                ArithmeticExpression(new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5)), '*'), '+')),
                                new CompoundStatement(new AssignmentStatement("b",new ArithmeticExpression(new VariableExpression("a"), new ValueExpression(new
                                        IntValue(1)), '+')), new PrintStatement(new VariableExpression("b"))))));
        runStatement(statement);
    }

    private static void runProgram3() throws GeneralException {
        IStatement statement = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompoundStatement(new IfStatement(new VariableExpression("a"),
                                        new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                                        new AssignmentStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v"))))));
        runStatement(statement);
    }

    private static void runStatement(IStatement statement) throws GeneralException {
        Controller controller = new Controller(true);
        controller.addProgram(statement);


        controller.executeAllSteps();
        System.out.println("Result: " + controller.getRepository().getCurrentProgramState().outToString());
    }
}
