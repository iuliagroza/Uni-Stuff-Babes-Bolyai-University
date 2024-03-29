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

    public void testAddStudent1()
    {
        Student testStudent = new Student("test_id", "Test Student", 933, "test_email@stud.ubbcluj.ro");
        try {
            service.addStudent(testStudent);
        } catch (Exception e){
            fail();
        }
        service.deleteStudent("test_id");
        assertTrue( true );
    }

    public void testAddStudent2()
    {
        Student testStudent = new Student("test_id", "Test Student", -933, "test_email@stud.ubbcluj.ro");
        try {
            service.addStudent(testStudent);
//            service.deleteStudent("test_id");
            fail();
        } catch (Exception e){
            assertTrue( true );
        }
    }

    public void testAddTema1()
    {
        Tema testTema = new Tema("test_tema", "test_description", 1, 10);
        try {
            service.addTema(testTema);
        } catch (Exception e){
            fail();
        }
        service.deleteTema("test_tema");
        assertTrue( true );
    }

    public void testAddTema2()
    {
        Tema testTema = new Tema("test_tema", "test_description", 1, 15);
        try {
            service.addTema(testTema);
            fail();
        } catch (Exception e){
            assertTrue( true );
        }
    }

    public void testCase1()
    {
        Student testStudent = new Student("1", "John Doe", 933, "johndoe@ubb.ro");
        try {
            service.addStudent(testStudent);
        } catch (Exception e){
            fail();
        }
        service.deleteStudent("1");
        assertTrue( true );
    }
    public void testCase2()
    {
        Student testStudent = new Student("2", "John Doe", -9, "johndoe@ubb.ro");
        try {
            service.addStudent(testStudent);
            fail();
        } catch (ValidationException e) {
            assertTrue(true);
        }
    }

    public void testCase3()
    {
        Student testStudent = new Student("3", "John Doe", 0, "johndoe@ubb.ro");
        try {
            service.addStudent(testStudent);
        } catch (Exception e){
            fail();
        }
        service.deleteStudent("3");
        assertTrue( true );
    }
    public void testCase5()
    {
        Student testStudent = new Student("1", "", 933, "johndoe@ubb.ro");
        try {
            service.addStudent(testStudent);
            fail();
        } catch (ValidationException e){
            assertTrue( true );
        }
    }
    public void testCase6()
    {
        Student testStudent = new Student("1", null, 933, "johndoe@ubb.ro");
        try {
            service.addStudent(testStudent);
            fail();
        } catch (ValidationException e){
            assertTrue( true );
        }
    }
    public void testCase7()
    {
        Student testStudent = new Student("2345", "John Doe", 0, "johndoe@ubb.ro");
        try {
            service.addStudent(testStudent);
        } catch (Exception e){
            fail();
        }
        service.deleteStudent("2345");
        assertTrue( true );
    }
    public void testCase8()
    {
        Student testStudent = new Student("", "John Doe", 933, "johndoe@ubb.ro");
        try {
            service.addStudent(testStudent);
            fail();
        } catch (ValidationException e){
            assertTrue( true );
        }
    }
    public void testCase9()
    {
        Student testStudent = new Student(null, "John Doe", 933, "johndoe@ubb.ro");
        try {
            service.addStudent(testStudent);
            fail();
        } catch (ValidationException e){
            assertTrue( true );
        }
    }
    public void testCase11()
    {
        Student testStudent = new Student("2", "John Doe", 933, "");
        try {
            service.addStudent(testStudent);
            fail();
        } catch (ValidationException e){
            assertTrue( true );
        }
    }
    public void testCase12()
    {
        Student testStudent = new Student("2", "John Doe", 933, null);
        try {
            service.addStudent(testStudent);
            fail();
        } catch (ValidationException e){
            assertTrue( true );
        }
    }
    public void testCase13()
    {
        Student testStudent = new Student("1", "John Doe", 0, "johndoe@ubb.ro");
        service.addStudent(testStudent);
        try {
            service.addStudent(testStudent);
        } catch (Exception e){
            fail();
        }
        service.deleteStudent("1");
        assertTrue( true );
    }
    public void testCase14()
    {
        Student testStudent = new Student("1", "John Doe", 0, "johndoe@ubb.ro");
        service.addStudent(testStudent);

        testStudent = new Student("2", "John Doe", 0, "johndoe@ubb.ro");
        try {
            service.addStudent(testStudent);
        } catch (Exception e){
            fail();
        }
        service.deleteStudent("1");
        service.deleteStudent("2");
        assertTrue( true );
    }
}
