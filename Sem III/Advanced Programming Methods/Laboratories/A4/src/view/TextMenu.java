package view;

import exceptions.ADTException;
import model.adt.ADTDictionary;
import view.command.Command;

import java.util.Scanner;

public class TextMenu {
    private final ADTDictionary<String, Command> commands;

    public TextMenu() {
        commands = new ADTDictionary<>();
    }

    public void addCommand(Command command) {
        commands.put(command.getKey(), command);
    }

    private void printMenu() {
        for (Command command: commands.getDictionary().values()) {
            String line = String.format("%s. %s", command.getKey(), command.getDescription());
            System.out.println(line);
        }
    }

    public void show() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("Input the number associated to your option: ");
            printMenu();
            System.out.println(">>> ");

            try {
                String key = scanner.nextLine();

                boolean valid = false;
                for (int i = 1; i <= commands.getDictionary().size(); i++) {
                    if (key.equals(Integer.toString(i))) {
                        valid = true;
                    }
                }
                if(!valid) {
                    throw new ADTException("Invalid input!");
                }

                Command command = commands.get(key);
                command.execute();
            } catch(ADTException e) {
                System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
            }
        }
    }
}
