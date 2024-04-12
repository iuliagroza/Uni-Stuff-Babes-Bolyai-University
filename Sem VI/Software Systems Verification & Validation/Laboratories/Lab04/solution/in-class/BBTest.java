package ssvv.lab1;

import curent.Curent;
import domain.Nota;
import domain.Student;
import domain.Tema;
import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import repository.NotaXMLRepo;
import repository.StudentXMLRepo;
import repository.TemaXMLRepo;
import service.Service;
import validation.NotaValidator;
import validation.StudentValidator;
import validation.TemaValidator;
import validation.ValidationException;

import java.time.LocalDate;

/**
 * Unit test for simple App.
 */
public class BBTest
        extends TestCase {
    StudentValidator studentValidator = new StudentValidator();
    TemaValidator temaValidator = new TemaValidator();
    String filenameStudent = "fisiere/Studenti.xml";
    String filenameTema = "fisiere/Teme.xml";
    String filenameNota = "fisiere/Note.xml";

    StudentXMLRepo studentXMLRepository = new StudentXMLRepo(filenameStudent);
    TemaXMLRepo temaXMLRepository = new TemaXMLRepo(filenameTema);
    NotaValidator notaValidator = new NotaValidator(studentXMLRepository, temaXMLRepository);
    NotaXMLRepo notaXMLRepository = new NotaXMLRepo(filenameNota);
    Service service = new Service(studentXMLRepository, studentValidator, temaXMLRepository, temaValidator, notaXMLRepository, notaValidator);

    /**
     * Create the test case
     *
     * @param testName name of the test case
     */
    public BBTest(String testName) {
        super(testName);
    }

    /**
     * @return the suite of tests being tested
     */
    public static Test suite() {
        return new TestSuite(BBTest.class);
    }

    public void testAddStudent() {
        Student testStudent = new Student("test_id", "Test Student", 933, "test_email@stud.ubbcluj.ro");
        try {
            service.addStudent(testStudent);
        } catch (Exception e) {
            fail();
        }
        service.deleteStudent("test_id");
        assertTrue(true);
    }

    public void testAddAssignment() {
        Tema testTema = new Tema("test_tema", "test_description", 1, 10);
        try {
            service.addTema(testTema);
        } catch (Exception e) {
            fail();
        }
        service.deleteTema("test_tema");
        assertTrue(true);
    }

    public void testAddGrade() {
        Nota testNota = new Nota("test_nota", "1003", "1", 9.0, LocalDate.now());
        try {
            service.addNota(testNota, "test_feedback");
        } catch (Exception e) {
            fail();
        }
        service.deleteNota("test_nota");
        assertTrue(true);
    }

    public void testIntegAdd() {
        Student testStudent = new Student("test_id", "Test Student", 933, "test_email@stud.ubbcluj.ro");
        Tema testTema = new Tema("test_tema", "test_description", 14, 1);
        Nota testNota = new Nota("test_nota", "test_id", "test_tema", 9.0, LocalDate.now());

        try {
            service.addStudent(testStudent);
            service.addTema(testTema);
            service.addNota(testNota, "test_feedback");
        } catch (Exception e) {
            System.out.print(e.toString());
            fail();
        }
        service.deleteNota("test_nota");
        service.deleteTema("test_tema");
        service.deleteStudent("test_id");
        assertTrue(true);
    }

}
