package view;

import domain.Nota;
import domain.Student;
import domain.Tema;
import service.Service;
import validation.ValidationException;
import java.time.LocalDate;
import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * Interfata utilizator de tip consola
 */
public class UI {
    private Service service;

    /**
     * Class constructor
     * @param service - service-ul clasei
     */
    public UI(Service service) {
        this.service = service;
    }

    /**
     * Metoda care ruleaza aplicatia
     */
    public void run() {
        System.out.println("Bine ati venit!");
        while (true) {
            try {
                System.out.println("Meniu comenzi: ");
                System.out.println("0.Exit");
                System.out.println("1.Comenzi student");
                System.out.println("2.Comenzi teme");
                System.out.println("3.Comenzi note");
                Scanner scanner = new Scanner(System.in);
                System.out.print("Introduceti comanda: ");
                int comanda = scanner.nextInt();
                if (comanda == 0) {
                    System.out.println("La revedere!");
                    break;
                } else if (comanda == 1) {
                    meniuStudent();
                } else if (comanda == 2) {
                    meniuTeme();
                } else if (comanda == 3) {
                    meniuNote();
                } else {
                    System.out.println("Comanda invalida!");
                }
            } catch (ValidationException exception) {
                System.out.println(exception.getMessage());
            } catch (InputMismatchException exception) {
                System.out.println("Date introduse gresit!");
            } catch (ArrayIndexOutOfBoundsException exception) {
                System.out.println("Eroare la introducerea datelor!");
            }
        }
    }

    /**
     * Afiseaza meniul de comenzi asupra studentilor
     */
    private void meniuStudent() {
        while (true) {
            System.out.println("\n0.Iesire meniu student");
            System.out.println("1.Introducere student");
            System.out.println("2.Stergere student");
            System.out.println("3.Cautare student");
            System.out.println("4.Modificare student");
            System.out.println("5.Afisare lista studenti");
            Scanner scanner = new Scanner(System.in);
            System.out.print("Introduceti comanda: ");
            int comanda = scanner.nextInt();
            if (comanda == 0) {
                break;
            } else if (comanda == 1) {
                adaugaStudent();
            } else if (comanda == 2) {
                stergeStudent();
            } else if (comanda == 3) {
                cautareStudent();
            } else if (comanda == 4) {
                updateStudent();
            } else if (comanda == 5) {
                afisareStudenti();
            } else {
                System.out.println("Comanda invalida!");
            }
        }
    }

    /**
     * Adauga un student
     * @throws ValidationException daca datele studentul exista deja
     */
    private void adaugaStudent() throws ValidationException {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id student: ");
        String idStudent = scanner.next();
        if (service.findStudent(idStudent) != null) {
            throw new ValidationException("Studentul exista!");
        }
        System.out.print("Introduceti numele: ");
        scanner.nextLine();
        String numeStudent = scanner.nextLine();
        System.out.print("Introduceti grupa: ");
        int grupa = scanner.nextInt();
        System.out.print("Introduceti email: ");
        String email = scanner.next();
        Student student = new Student(idStudent, numeStudent, grupa, email);
        Student student1 = service.addStudent(student);
        if (student1 == null) {
            System.out.println("Student adaugat cu succes!");
        } else {
            System.out.println("Studentul deja exista" + student1);
        }
    }

    /**
     * Sterge un student
     */
    private void stergeStudent() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id-ul student: pe care doriti sa il stergeti: ");
        String id = scanner.next();
        Student student = service.deleteStudent(id);
        if (student == null) {
            System.out.println("Studentul nu exista!");
        } else {
            System.out.println("Student sters cu succes!");
        }
    }

    /**
     * Cauta un student
     */
    private void cautareStudent() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id-ul studentului: ");
        String id = scanner.next();
        Student student = service.findStudent(id);
        if (student == null) {
            System.out.println("Studentul nu exista!");
        } else {
            System.out.println(student);
        }
    }

    /**
     * Modifica datele unui student
     */
    private void updateStudent() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id-ul studentului pe care doriti sa il modificati: ");
        String id = scanner.next();
        System.out.println("Introduceti datele noi");
        System.out.print("Introduceti numele: ");
        scanner.nextLine();
        String nume = scanner.nextLine();
        System.out.print("Introduceti grupa: ");
        int grupa = scanner.nextInt();
        System.out.print("Introduceti email: ");
        String email = scanner.next();
        Student student = new Student(id, nume, grupa, email);
        Student student1 = service.updateStudent(student);
        if (student1 == null) {
            System.out.print("Studentul nu exista!");
        } else {
            System.out.println("Student modificat cu succes!" + student1);
        }
    }

    /**
     * Afiseaza lista studentilor
     */
    private void afisareStudenti() {
        Iterable<Student> all = service.getAllStudenti();
        all.forEach(student ->
                System.out.println(student)
        );
    }

    /**
     * Afiseaza comenzile pentru teme
     */
    private void meniuTeme() {
        while (true) {
            System.out.println("\n0.Iesire meniu teme");
            System.out.println("1.Introducere tema");
            System.out.println("2.Prelungire deadline");
            System.out.println("3.Stergere tema");
            System.out.println("4.Cautare tema");
            System.out.println("5.Modificare tema");
            System.out.println("6.Afisare lista teme");
            Scanner scanner = new Scanner(System.in);
            System.out.print("Introduceti comanda: ");
            int comanda = scanner.nextInt();
            if (comanda == 0) {
                break;
            } else if (comanda == 1) {
                adaugaTema();
            }
            else if(comanda==2) {
                prelungireDeadline();
            }
            else if (comanda == 3) {
                stergeTema();
            } else if (comanda == 4) {
                cautareTema();
            } else if (comanda == 5) {
                updateTema();
            } else if (comanda == 6) {
                afisareTeme();
            } else {
                System.out.println("Comanda invalida!");
            }
        }
    }

    /**
     * Adauga o tema
     * @throws ValidationException daca tema exista deja
     */
    private void adaugaTema() throws ValidationException{
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti nr tema: ");
        String nrTema = scanner.next();
        if (service.findTema(nrTema) != null) {
            throw new ValidationException("Tema exista deja!");
        }
        System.out.print("Introduceti descrierea: ");
        scanner.nextLine();
        String descriere = scanner.nextLine();
        System.out.print("Introduceti deadline-ul(nr saptamanii): ");
        int deadline = scanner.nextInt();
        System.out.print("Introduceti saptamana primirii: ");
        int primire = scanner.nextInt();
        Tema tema = new Tema(nrTema, descriere, deadline, primire);
        tema = service.addTema(tema);
        if (tema == null) {
            System.out.println("Tema adaugata cu succes!");
        } else {
            System.out.println("Tema deja exista" + tema);
        }
    }


    /**
     * Prelungeste deadline-ul unei teme
     */
    private void prelungireDeadline(){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id tema: ");
        String nrTema = scanner.next();
        System.out.print("Introduceti deadline nou: ");
        int deadline = scanner.nextInt();
        service.prelungireDeadline(nrTema, deadline);
        System.out.println("Dealine prelungit!");
    }

    /**
     * Sterge o tema
     */
    private void stergeTema() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id-ul temei: pe care doriti sa o stergeti: ");
        String id = scanner.next();
        Tema tema = service.deleteTema(id);
        if (tema == null) {
            System.out.println("Tema nu exista!");
        } else {
            System.out.println("Tema stearsa cu succes!");
        }
    }

    /**
     * Cauta o tema
     */
    private void cautareTema() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id-ul temei: ");
        String id = scanner.next();
        Tema tema = service.findTema(id);
        if (tema == null) {
            System.out.println("Tema nu exista!");
        } else {
            System.out.println(tema);
        }
    }

    /**
     * Modifica o tema
     */
    private void updateTema() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id-ul temei pe care doriti sa o modificati: ");
        String id = scanner.next();
        System.out.println("Introduceti datele noi");
        System.out.print("Introduceti descrierea: ");
        scanner.nextLine();
        String descriere = scanner.nextLine();
        System.out.print("Introduceti deadline: ");
        int deadline = scanner.nextInt();
        System.out.print("Introduceti saptamana primire: ");
        int primire = scanner.nextInt();
        Tema tema = new Tema(id, descriere, deadline, primire);
        Tema tema1 = service.updateTema(tema);
        if (tema1 == null) {
            System.out.println("Tema nu exista!");
        } else {
            System.out.println("Tema modificata cu succes!" + tema1);
        }
    }

    /**
     * Afiseaza toate temele
     */
    private void afisareTeme(){
        Iterable<Tema> all = service.getAllTeme();
        //for(Tema tema: all){
        //    System.out.println(tema);
        //}
        all.forEach(tema -> System.out.println(tema));
    }

    /**
     * Afiseaza comenzile disponibile pentru note
     */
    private void meniuNote() {
        while (true) {
            System.out.println("\n0.Iesire meniu note");
            System.out.println("1.Introducere nota");
            System.out.println("2.Stergere nota");
            System.out.println("3.Cautare nota");
            System.out.println("4.Afisare lista note");
            Scanner scanner = new Scanner(System.in);
            System.out.print("Introduceti comanda: ");
            int comanda = scanner.nextInt();
            if (comanda == 0) {
                break;
            } else if (comanda == 1) {
                adaugaNota();
            } else if (comanda == 2) {
                stergeNota();
            } else if (comanda == 3) {
                cautareNota();
            } else if (comanda == 4) {
                afisareNote();
            } else {
                System.out.println("Comanda invalida!");
            }
        }
    }

    /**
     * Adauga o nota
     * @throws ValidationException daca nota exista deja
     */
    private void adaugaNota() throws ValidationException {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id student: ");
        String idStudent = scanner.next();
        System.out.print("Introduceti numarul temei: ");
        String nrTema = scanner.next();
        String idNota = idStudent + "#" + nrTema;
        if (service.findNota(idNota) != null) {
            throw new ValidationException("Nota exista deja!");
        }
        System.out.print("Introduceti nota: ");
        Double nota = scanner.nextDouble();
        System.out.print("Introduceti data predarii temei(format: an-luna-data): ");
        String data = scanner.next();
        String[] date = data.split("-");
        LocalDate dataPredare = LocalDate.of(Integer.parseInt(date[0]), Integer.parseInt(date[1]), Integer.parseInt(date[2]));
        System.out.print("Introduceti feedback: ");
        scanner.nextLine();
        String feedback = scanner.nextLine();        //System.out.println(feedback);
        Nota notaCatalog = new Nota(idNota, idStudent, nrTema, nota, dataPredare);
        double notaFinala = service.addNota(notaCatalog, feedback);
        System.out.println("Nota maxima pe care o poate primi studentul este: " + notaFinala);
    }

    /**
     * Sterge o nota
     */
    private void stergeNota() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id-ul studentului: ");
        String idStudent = scanner.next();
        System.out.print("Introduceti nr-ul temei: ");
        String nrTema = scanner.next();
        String idNota = idStudent + "#" + nrTema;
        Nota nota = service.deleteNota(idNota);
        if (nota == null) {
            System.out.println("Nota nu exista!");
        } else {
            System.out.println("Nota stearsa cu succes!");
        }
    }

    /**
     * Cauta o nota
     */
    private void cautareNota() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduceti id-ul studentului: ");
        String idStudent = scanner.next();
        System.out.print("Introduceti nr-ul temei: ");
        String nrTema = scanner.next();
        String idNota = idStudent + "#" + nrTema;
        Nota nota = service.findNota(idNota);
        if (nota == null) {
            System.out.println("Nota nu exista!");
        } else {
            System.out.println(nota);
        }
    }

    /**
     * Afiseaza toate notele
     */
    private void afisareNote() {
        Iterable<Nota> all = service.getAllNote();
        all.forEach(nota ->
                System.out.println(nota)
        );
    }
}
