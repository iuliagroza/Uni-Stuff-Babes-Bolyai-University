package view.gui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.util.Objects;

public class GUI extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader programListLoader = new FXMLLoader();
        programListLoader.setLocation(GUI.class.getResource("resources/ProgramSelect.fxml"));
        Parent programListRoot = programListLoader.load();
        Scene programListScene = new Scene(programListRoot, 500, 550);
        programListScene.getStylesheets().add(Objects.requireNonNull(GUI.class.getResource("resources/style.css")).toExternalForm());
        ProgramSelect programChooserController = programListLoader.getController();
        primaryStage.setTitle("Select a program");
        primaryStage.setScene(programListScene);
        primaryStage.show();

        FXMLLoader programExecutorLoader = new FXMLLoader();
        programExecutorLoader.setLocation(GUI.class.getResource("resources/ProgramExecutor.fxml"));
        Parent programExecutorRoot = programExecutorLoader.load();
        Scene programExecutorScene = new Scene(programExecutorRoot, 700, 500);
        programExecutorScene.getStylesheets().add(Objects.requireNonNull(GUI.class.getResource("resources/style.css")).toExternalForm());
        ProgramExecutor programExecutor = programExecutorLoader.getController();
        programChooserController.setProgramExecutor(programExecutor);
        Stage secondaryStage = new Stage();
        secondaryStage.setTitle("Interpreter");
        secondaryStage.setScene(programExecutorScene);
        secondaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}