package view;

import controller.Controller;
import model.expressions.*;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.ReferenceType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import repository.IRepository;
import repository.Repository;
import view.command.ExitCommand;
import view.command.RunExampleCommand;

public class Interpreter {
    public static void main(String[] args) {
        /* int v; v=2; Print(v) */
        IStatement ex1 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()), new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));
        IRepository repo1 = new Repository("log1.txt");
        Controller controller1 = new Controller(repo1, true);
        controller1.addProgram(ex1);

        /* int a; int b; a=2+3*5; b=a+1; Print(b) */
        IStatement ex2 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()), new CompoundStatement(new VariableDeclarationStatement("b", new IntType()), new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression(new ValueExpression(new IntValue(2)), new ArithmeticExpression(new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5)), '*'), '+')), new CompoundStatement(new AssignmentStatement("b", new ArithmeticExpression(new VariableExpression("a"), new ValueExpression(new IntValue(1)), '+')), new PrintStatement(new VariableExpression("b"))))));

        IRepository repo2 = new Repository("log2.txt");
        Controller controller2 = new Controller(repo2, true);
        controller2.addProgram(ex2);

        /* bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v) */
        IStatement ex3 = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()), new CompoundStatement(new VariableDeclarationStatement("v", new IntType()), new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))), new CompoundStatement(new IfStatement(new VariableExpression("a"), new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));

        IRepository repo3 = new Repository("log3.txt");
        Controller controller3 = new Controller(repo3, true);
        controller3.addProgram(ex3);

        /* string varf; varf = "test.in"; OpenReadFile("varf"); int varc; ReadFile("varf", "varc"); Print(varc);
           ReadFile("varf", "varc"); Print(varc); CloseReadFile("varf")  */
        IStatement ex4 = new CompoundStatement(new VariableDeclarationStatement("varf", new StringType()), new CompoundStatement(new AssignmentStatement("varf", new ValueExpression(new StringValue("test.in"))), new CompoundStatement(new OpenReadFileStatement(new VariableExpression("varf")), new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()), new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompoundStatement(new PrintStatement(new VariableExpression("varc")), new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompoundStatement(new PrintStatement(new VariableExpression("varc")), new CloseReadFileStatement(new VariableExpression("varf"))))))))));

        IRepository repo4 = new Repository("log4.txt");
        Controller controller4 = new Controller(repo4, true);
        controller4.addProgram(ex4);

        /* int a; int b; a=5; b=7; (If a>b Then Print(a) Else Print(b)) */
        IStatement ex5 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()), new CompoundStatement(new VariableDeclarationStatement("b", new IntType()), new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new IntValue(5))), new CompoundStatement(new AssignmentStatement("b", new ValueExpression(new IntValue(7))), new IfStatement(new RelationalExpression(new VariableExpression("a"), new VariableExpression("b"), ">"), new PrintStatement(new VariableExpression("a")), new PrintStatement(new VariableExpression("b")))))));

        IRepository repo5 = new Repository("log5.txt");
        Controller controller5 = new Controller(repo5, true);
        controller5.addProgram(ex5);

        /* int v; v=4; (while (v>0) print(v); v=v-1); print(v) */
        IStatement ex6 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()), new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(4))), new CompoundStatement(new WhileStatement(new RelationalExpression(new VariableExpression("v"), new ValueExpression(new IntValue(0)), ">"), new CompoundStatement(new PrintStatement(new VariableExpression("v")), new AssignmentStatement("v", new ArithmeticExpression(new VariableExpression("v"), new ValueExpression(new IntValue(1)), '-')))), new PrintStatement(new VariableExpression("v")))));

        IRepository repo6 = new Repository("log6.txt");
        Controller controller6 = new Controller(repo6, true);
        controller6.addProgram(ex6);

        /* Ref int v; new(v,20); Ref Ref int a; new(a,v); print(v); print(a) */
        IStatement ex7 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))), new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")), new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a")))))));

        IRepository repo7 = new Repository("log7.txt");
        Controller controller7 = new Controller(repo7, true);
        controller7.addProgram(ex7);

        /* Ref int v; new(v,20); Ref Ref int a; new(a,v); print(rH(v)); print(rH(rH(a))+5) */
        IStatement ex8 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new PrintStatement(new HeapReadExpression(new VariableExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression(new HeapReadExpression(new HeapReadExpression(new VariableExpression("a"))), new ValueExpression(new IntValue(5)), '+')))))));

        IRepository repo8 = new Repository("log8.txt");
        Controller controller8 = new Controller(repo8, true);
        controller8.addProgram(ex8);

        /* Ref int v; new(v,20); print(rH(v)); wH(v,30); print(rH(v)+5); */
        IStatement ex9 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement( new PrintStatement(new HeapReadExpression(new VariableExpression("v"))),
                                new CompoundStatement(new HeapWriteStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression( new HeapReadExpression(new VariableExpression("v")), new ValueExpression(new IntValue(5)), '+'))))));

        IRepository repo9 = new Repository("log9.txt");
        Controller controller9 = new Controller(repo9, true);
        controller9.addProgram(ex9);

        /* Ref int v; new(v,20); Ref Ref int a; new(a,v); new(v,30); print(rH(rH(a))) */
        IStatement ex10 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new HeapReadExpression(new HeapReadExpression(new VariableExpression("a")))))))));

        IRepository repo10 = new Repository("log10.txt");
        Controller controller10 = new Controller(repo10, true);
        controller10.addProgram(ex10);

        /* int v; Ref int a; v=10; new(a,22); fork(wH(a,30); v=32; print(v); print(rH(a))); print(v); print(rH(a)) */
        IStatement ex11 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                        new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                                new CompoundStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                                        new CompoundStatement(new ForkStatement(new CompoundStatement(new HeapWriteStatement("a", new ValueExpression(new IntValue(30))),
                                                new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new HeapReadExpression(new VariableExpression("a"))))))),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new HeapReadExpression(new VariableExpression("a")))))))));

        IRepository repo11 = new Repository("log11.txt");
        Controller controller11 = new Controller(repo11, true);
        controller11.addProgram(ex11);

        TextMenu menu = new TextMenu();

        menu.addCommand(new RunExampleCommand("1", ex1.toString(), controller1));
        menu.addCommand(new RunExampleCommand("2", ex2.toString(), controller2));
        menu.addCommand(new RunExampleCommand("3", ex3.toString(), controller3));
        menu.addCommand(new RunExampleCommand("4", ex4.toString(), controller4));
        menu.addCommand(new RunExampleCommand("5", ex5.toString(), controller5));
        menu.addCommand(new RunExampleCommand("6", ex6.toString(), controller6));
        menu.addCommand(new RunExampleCommand("7", ex7.toString(), controller7));
        menu.addCommand(new RunExampleCommand("8", ex8.toString(), controller8));
        menu.addCommand(new RunExampleCommand("9", ex9.toString(), controller9));
        menu.addCommand(new RunExampleCommand("10", ex10.toString(), controller10));
        menu.addCommand(new RunExampleCommand("11", ex11.toString(), controller11));
        menu.addCommand(new ExitCommand("12", "Exit."));

        menu.show();
    }
}
