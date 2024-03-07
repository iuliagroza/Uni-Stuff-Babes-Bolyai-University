package view.gui;

import controller.Controller;
import exceptions.ExpressionException;
import exceptions.StatementException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import model.expressions.*;
import model.programstate.ProgramState;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.ReferenceType;
import model.types.StringType;
import model.adt.ADTDictionary;
import model.adt.ADTHeap;
import model.adt.ADTList;
import model.adt.ADTStack;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import repository.IRepository;
import repository.Repository;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ProgramSelect {
    private ProgramExecutor programExecutor;

    public void setProgramExecutor(ProgramExecutor programExecutor) {
        this.programExecutor = programExecutor;
    }
    @FXML
    private ListView<IStatement> programsListView;

    @FXML
    private Button displayButton;

    @FXML
    public void initialize() {
        programsListView.setItems(getAllStatements());
        programsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }

    @FXML
    private void displayProgram(ActionEvent actionEvent) {
        IStatement selectedStatement = programsListView.getSelectionModel().getSelectedItem();
        if (selectedStatement == null) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error encountered!");
            alert.setContentText("No statement selected!");
            alert.showAndWait();
        } else {
            int id = programsListView.getSelectionModel().getSelectedIndex();
            try {
                selectedStatement.typeCheck(new ADTDictionary<>());
                IRepository repository = new Repository("log" + (id + 1) + ".txt");
                Controller controller = new Controller(repository, true);
                controller.addProgram(selectedStatement);
                programExecutor.setController(controller);
            } catch (StatementException | ExpressionException exception) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error encountered!");
                alert.setContentText(exception.getMessage());
                alert.showAndWait();
            }
        }
    }

    @FXML
    private ObservableList<IStatement> getAllStatements() {
        List<IStatement> allStatements = new ArrayList<>();

        /* int v; v=2; Print(v) */
        IStatement ex1 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));
        allStatements.add(ex1);

        /* int a; int b; a=2+3*5; b=a+1; Print(b) */
        IStatement ex2 = new CompoundStatement(new VariableDeclarationStatement(
                "a", new IntType()), new CompoundStatement(
                        new VariableDeclarationStatement("b", new IntType()),
                new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression(
                        new ValueExpression(new IntValue(2)), new ArithmeticExpression(
                                new ValueExpression(new IntValue(3)), new ValueExpression(
                                        new IntValue(5)), '*'), '+')),
                        new CompoundStatement(new AssignmentStatement("b", new ArithmeticExpression(new VariableExpression("a"), new ValueExpression(new IntValue(1)), '+')), new PrintStatement(new VariableExpression("b"))))));
        allStatements.add(ex2);

        /* bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v) */
        IStatement ex3 = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()), new CompoundStatement(new VariableDeclarationStatement("v", new IntType()), new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))), new CompoundStatement(new IfStatement(new VariableExpression("a"), new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));
        allStatements.add(ex3);

        /* string varf; varf = "test.in"; OpenReadFile("varf"); int varc; ReadFile("varf", "varc"); Print(varc);
           ReadFile("varf", "varc"); Print(varc); CloseReadFile("varf")  */
        IStatement ex4 = new CompoundStatement(new VariableDeclarationStatement("varf", new BoolType()), new CompoundStatement(new AssignmentStatement("varf", new ValueExpression(new StringValue("test.in"))), new CompoundStatement(new OpenReadFileStatement(new VariableExpression("varf")), new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()), new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompoundStatement(new PrintStatement(new VariableExpression("varc")), new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompoundStatement(new PrintStatement(new VariableExpression("varc")), new CloseReadFileStatement(new VariableExpression("varf"))))))))));
        allStatements.add(ex4);

        /* int a; int b; a=5; b=7; (If a>b Then Print(a) Else Print(b)) */
        IStatement ex5 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()), new CompoundStatement(new VariableDeclarationStatement("b", new IntType()), new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new IntValue(5))), new CompoundStatement(new AssignmentStatement("b", new ValueExpression(new IntValue(7))), new IfStatement(new RelationalExpression(new VariableExpression("a"), new VariableExpression("b"), ">"), new PrintStatement(new VariableExpression("a")), new PrintStatement(new VariableExpression("b")))))));
        allStatements.add(ex5);

        /* int v; v=4; (while (v>0) print(v); v=v-1); print(v) */
        IStatement ex6 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()), new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(4))), new CompoundStatement(new WhileStatement(new RelationalExpression(new VariableExpression("v"), new ValueExpression(new IntValue(0)), ">"), new CompoundStatement(new PrintStatement(new VariableExpression("v")), new AssignmentStatement("v", new ArithmeticExpression(new VariableExpression("v"), new ValueExpression(new IntValue(1)), '-')))), new PrintStatement(new VariableExpression("v")))));
        allStatements.add(ex6);

        /* Ref int v; new(v,20); Ref Ref int a; new(a,v); print(v); print(a) */
        IStatement ex7 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))), new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")), new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a")))))));
        allStatements.add(ex7);

        /* Ref int v; new(v,20); Ref Ref int a; new(a,v); print(rH(v)); print(rH(rH(a))+5) */
        IStatement ex8 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))), new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")), new CompoundStatement(new PrintStatement(new HeapReadExpression(new VariableExpression("v"))), new PrintStatement(new ArithmeticExpression(new HeapReadExpression(new HeapReadExpression(new VariableExpression("a"))), new ValueExpression(new IntValue(5)), '+')))))));
        allStatements.add(ex8);

        /* Ref int v; new(v,20); print(rH(v)); wH(v,30); print(rH(v)+5); */
        IStatement ex9 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))), new CompoundStatement(new PrintStatement(new HeapReadExpression(new VariableExpression("v"))), new CompoundStatement(new HeapWriteStatement("v", new ValueExpression(new IntValue(30))), new PrintStatement(new ArithmeticExpression(new HeapReadExpression(new VariableExpression("v")), new ValueExpression(new IntValue(5)), '+'))))));
        allStatements.add(ex9);

        /* Ref int v; new(v,20); Ref Ref int a; new(a,v); new(v,30); print(rH(rH(a))) */
        IStatement ex10 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))), new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))), new PrintStatement(new HeapReadExpression(new HeapReadExpression(new VariableExpression("a")))))))));
        allStatements.add(ex10);

        return FXCollections.observableArrayList(allStatements);
    }
}