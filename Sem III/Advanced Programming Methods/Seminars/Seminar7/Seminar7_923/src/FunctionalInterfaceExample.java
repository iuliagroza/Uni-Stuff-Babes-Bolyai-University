import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

// A functional interface has exactly one abstract method
// Not necessarily to add the annotation, but it will throw a compilation error
@FunctionalInterface
public interface FunctionalInterfaceExample {
    void method();
}

@FunctionalInterface
interface FunctionalInterfaceDoingSomething {
    int methodDoingSmth(int a, int b);
}

// On extending the first interface, without adding any method, it will still be a functional interface
interface IsItFunctionalInterface extends FunctionalInterfaceExample {

    // If we add method2, the interface won't be a functional one anymore (two abstract methods)
    void method2();

    // If we'd add just a static method, this would still be a functional interface
    static void staticMethod() {

    }

    // Default methods have a body, so they are not abstract
    // This means that we can add as many default/static methods as we want, it will still be
    // a functional interface, given there is only one abstract method
    default void defaultMethod() {

    }
}

class Student {
    Student(String s) {

    }

    int getAge() {
        return 7;
    }
}

class FunctionalInterfaceImplementationExample {

    static String operation(String s) {
        return s.concat("whatever").toUpperCase();
    }

    public static void main(String[] args) {
        // For functional interfaces, we can create an instance if we give an implementation of the abstract method
        FunctionalInterfaceExample example = () -> System.out.println("hello");

        FunctionalInterfaceDoingSomething functionalInterfaceDoingSomething = (a, b) -> a + b;
        functionalInterfaceDoingSomething.methodDoingSmth(3, 5);

        // forbidden by me!!!
        // This is an anonymous class, but it will require to override all abstract methods... it's a biiiig nono
        IsItFunctionalInterface isItFunctionalInterface = new IsItFunctionalInterface() {
            @Override
            public void method2() {

            }

            @Override
            public void method() {

            }
        };

        // Predicate example
        Predicate<Integer> predicate = (a) -> a > 5;
        predicate.test(7);// true
        predicate.test(0); // false

        // Function example
        Function<String, Integer> function = (a) -> a.length();
        function.apply("whatever"); // 8

        // Stream example
        List<String> listOfStrings = Arrays.asList("string1", "string24", "less");

        // map, filter, reduce, collect

        // filter
        listOfStrings.stream().filter((String s) -> s.length() < 6); // "less"
        listOfStrings.stream().filter((String s) -> s.startsWith("string")); // "string1", "string24"
        listOfStrings.stream().filter((String s) -> s.endsWith("4")); // "string24"

        // map
        listOfStrings.stream().map(s -> s.length()); // 7, 8, 4
        listOfStrings.stream().map((String s) -> s.toUpperCase()); // "STRING1" "STRING24" "LESS"
        listOfStrings.stream().map((String s) -> new Student(s)); // new Student("string1") ...

        listOfStrings.stream().reduce("", (String a, String b) -> a.concat(b));
        listOfStrings.stream().map((String s) -> s.length()).reduce(0, (a, b) -> a + b);

        // method reference
        listOfStrings.stream().map(String::length); // 7, 8, 4
        listOfStrings.stream().map(String::toUpperCase); // "STRING1" "STRING24" "LESS"

        listOfStrings.stream().map(FunctionalInterfaceImplementationExample::operation);
        listOfStrings.stream().map(s -> new Student(s)).map(Student::getAge); // 7 7 7 7

        // collect
        listOfStrings.stream().map(String::toUpperCase).collect(Collectors.toList());
        listOfStrings.stream().map(String::toUpperCase).collect(Collectors.toSet());

        // thank God for this... but only starting java 17
        listOfStrings.stream().map(String::toUpperCase).toList();

        Optional<String> optional = listOfStrings.stream().filter(s -> s.length() < 5).findFirst(); // Optional<String> ("less")
        // checks whether the optional has a value
        if(optional.isPresent()) {
            // retrieves the optional value
            optional.get();
        }

    }

    // best practice, is to use an optional to wrap results that are nullable
    // this way we can avoid NPEs when the null check is uhm... overlooked
    Optional<Student> retrieveFromList() {
        // ...
        //return Optional.ofNullable(new Student("a"));
        return Optional.empty();
    }
}