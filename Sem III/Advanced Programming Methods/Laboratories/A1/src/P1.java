import java.util.Scanner;

class PositiveThrowable extends Throwable { }

public class P1 {
    public static void main(String[] args) {
        int n;
        Scanner myObj = new Scanner(System.in);
        System.out.println("Enter the number of integers: ");
        while(true) {
            try {
                n = Integer.parseInt(myObj.nextLine());
                if (n < 1) {
                    throw new PositiveThrowable();
                }
                break;
            } catch (NumberFormatException e) {
                System.out.println("Please provide a valid integer.");
            } catch (PositiveThrowable t) {
                System.out.println("The number of integers must be positive.");
            }
        }

        double avg = 0.0;
        System.out.println("Enter each integer on a new line: ");
        int n_copy = n;
        while (n_copy > 0) {
            try {
                int x = Integer.parseInt(myObj.nextLine());
                avg += x;
                n_copy--;
            }
            catch (NumberFormatException e) {
                System.out.println("Please provide a valid integer.");
            }
        }

        avg /= n;

        System.out.println("The average of the provided numbers is: " + avg);
    }
}