package ssvv.lab1;

import domain.Student;
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

/**
 * Unit test for simple App.
 */
public class AppTest 
    extends TestCase
{
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
    public AppTest( String testName )
    {
        super( testName );
    }

    /**
     * @return the suite of tests being tested
     */
    public static Test suite()
    {
        return new TestSuite( AppTest.class );
    }

    /**
     * Rigourous Test :-)
     */
    public void testApp()
    {
        assertTrue( true );
    }

    public void testAddStudent1()
    {
        Student testStudent = new Student("test_id", "Test Student", 933, "test_email@stud.ubbcluj.ro");
        try {
            service.addStudent(testStudent);
            assertTrue( true );
        } catch (Exception e){
            fail();
        }
    }

    public void testAddStudent2()
    {
        Student testStudent = new Student("test_id", "Test Student", -933, "test_email@stud.ubbcluj.ro");
        try {
            service.addStudent(testStudent);
            fail();
        } catch (Exception e){
            assertTrue( true );
        }
    }
}
