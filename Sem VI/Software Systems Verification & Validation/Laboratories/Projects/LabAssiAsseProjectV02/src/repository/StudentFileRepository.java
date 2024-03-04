package repository;

import domain.Student;

public class StudentFileRepository extends AbstractFileRepository<String, Student> {

    /**
     * Class constructor
     * @param filename - numele fisierului
     */
    public StudentFileRepository(String filename) {
        super(filename);
    }

    /**
     * Extrage informatia despre student dintr-un string
     * @param linie - stringul din care ia datele studentului
     * @return studentul
     */
    @Override
    public Student extractEntity(String linie) {
        String[] cuvinte = linie.split(",");
        return new Student(cuvinte[0], cuvinte[1], Integer.parseInt(cuvinte[2]), cuvinte[3]);
    }
}
