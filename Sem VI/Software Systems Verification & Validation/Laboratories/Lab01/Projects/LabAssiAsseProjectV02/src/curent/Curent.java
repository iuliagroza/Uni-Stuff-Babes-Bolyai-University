package curent;

import validation.ValidationException;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.time.LocalDate;
import static java.time.temporal.ChronoUnit.DAYS;

public class Curent {

    /**
     * @return the current week from the starting of university
     */
    public static int getCurrentWeek(){
        LocalDate startDate = Curent.getStartDate();
        LocalDate today = LocalDate.now();
        long days = DAYS.between(startDate, today);
        double diff = Math.ceil((double)days/7);
        return (int)diff;
    }

    /**
     * @return the date when university have started
     */
    public static LocalDate getStartDate() {
        String filename = "fisiere/DataInceput.txt";
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(filename))) {
            String line = bufferedReader.readLine();
            String[] words = line.split(",");
            return LocalDate.of(Integer.parseInt(words[0]), Integer.parseInt(words[1]), Integer.parseInt(words[2]));
        } catch (IOException exception) {
            throw new ValidationException(exception.getMessage());
        }
    }
}
