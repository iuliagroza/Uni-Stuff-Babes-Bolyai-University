class NameThrowable extends Throwable {}

class Person {
    String name;
    static String residence = "Romania";
    Person(String name) {
        this.name = name;
    }

    static void Greet() {
        System.out.println("Hello!");
    }

    void GreetWithName() {
        try {
            if (name.equals("")) {
                throw new NameThrowable();
            }
            System.out.println("Hello, my name is " + name + "!");
        } catch(NameThrowable t) {
            System.out.println("Name must not be empty!");
        }
    }
}

class Teacher extends Person {
    Teacher(String name) {
        super(name);
    }

    void GreetWithName() {
        System.out.println("Hello, I'm a teacher! My name is " + name + "!");
    }
}

class Student extends Person {
    Student(String name) {
        super(name);
    }

    void GreetWithName() {
        System.out.println("Hello, I'm a student! My name is " + name + "!");
    }
}

public class P2 {
    public static void main(String[] args) {
        Person.Greet();
        System.out.println("We are living in " + Person.residence + ".");

        Person p1 = new Person("Jane");
        p1.GreetWithName();

        Person p2 = new Person("");
        p2.GreetWithName();

        Teacher t = new Teacher("John");
        t.GreetWithName();

        Student s = new Student("Mark");
        s.GreetWithName();
    }
}