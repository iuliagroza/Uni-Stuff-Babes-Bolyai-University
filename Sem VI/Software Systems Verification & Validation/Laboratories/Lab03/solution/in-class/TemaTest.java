package ssvv.lab1;

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

/**
 * Unit test for simple App.
 */
public class TemaTest
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
    public TemaTest(String testName) {
        super(testName);
    }

    /**
     * @return the suite of tests being tested
     */
    public static Test suite() {
        return new TestSuite(TemaTest.class);
    }


    public void testAddTema1() {
        Tema testTema = new Tema("test_tema", "test_description", 1, 10);
        try {
            service.addTema(testTema);
        } catch (Exception e) {
            fail();
        }
        service.deleteTema("test_tema");
        assertTrue(true);
    }

    public void testAddTema2() {
        Tema testTema = new Tema("test_tema", "test_description", 1, 15);
        try {
            service.addTema(testTema);
            fail();
        } catch (Exception e) {
            assertTrue(true);
        }
    }

    public void testTC2() {
        Tema testTema = new Tema("", "", 8, 6);
        try {
            service.addTema(testTema);
            fail();
        } catch (ValidationException e) {
            if (!e.getMessage().equals("Numar tema invalid!")) {
                fail();
            }
        }
    }

    public void testTC3() {
        Tema testTema = new Tema(null, "desc", 8, 6);
        try {
            service.addTema(testTema);
            fail();
        } catch (NullPointerException e) {
            assertTrue(true);
        }
    }

    public void testTC4() {
        Tema testTema = new Tema("1", "", 8, 6);
        try {
            service.addTema(testTema);
            fail();
        } catch (ValidationException e) {
            if (!e.getMessage().equals("Descriere invalida!")) {
                fail();
            }
        }
    }

    public void testTC5() {
        Tema testTema = new Tema("1", "desc", 15, 6);
        try {
            service.addTema(testTema);
            fail();
        } catch (ValidationException e) {
            if (!e.getMessage().equals("Deadlineul trebuie sa fie intre 1-14.")) {
                fail();
            }
        }
    }

    public void testTC6() {
        Tema testTema = new Tema("1", "desc", 8, -1);
        try {
            service.addTema(testTema);
            fail();
        } catch (ValidationException e) {
            if (!e.getMessage().equals("Saptamana primirii trebuie sa fie intre 1-14.")) {
                fail();
            }
        }
    }
}
