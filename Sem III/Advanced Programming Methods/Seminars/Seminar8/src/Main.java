import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,14,15);

        String result = numbers.stream().filter(n -> (n % 3 == 0 || n % 2 == 0)).map(n -> "A" + (n+1) + "AB")
                .collect(Collectors.joining());
        System.out.println(result);

        List<Integer> numbers2 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,14,15,16);

        int result2 = numbers2.stream().filter(n -> n % 4 == 0).map(n -> n+1).reduce(0, (a, b) -> (a + b) % 2);
        System.out.println(result2);
    }
}