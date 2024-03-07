import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        List<String> words = Arrays.asList("hi", "hello", "adss", "adfsb", "dafsgd");

        words.stream().forEach(s -> System.out.println("  " + s));

        words.stream().forEach(System.out::println);

        List<String> transformedWords1 = words.stream().map(s -> s + "!").collect(Collectors.toList());
        List<String> transformedWords2 = words.stream().map(s -> s.replace("i", "eye")).collect(Collectors.toList());
        List<String> transformedWords3 = words.stream().map(String::toUpperCase).collect(Collectors.toList());

        List<String> transformedWords4 = words.stream().filter(s -> s.length() < 4).collect(Collectors.toList());
        List<String> transformedWords5 = words.stream().filter(s -> s.contains("b")).collect(Collectors.toList());
        List<String> transformedWords6 = words.stream().filter(s -> (s.length() % 2) == 0).collect(Collectors.toList());

        System.out.println(words.stream().map(String::toUpperCase).filter(s -> s.length() < 4).filter(s -> s.contains("E")).findFirst());
        System.out.println(words.stream().map(String::toUpperCase).filter(s -> s.length() < 4).filter(s -> s.indexOf("Q") != -1).findFirst());
    }
}