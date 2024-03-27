package repository;

import domain.Student;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

public class StudentXMLRepo extends AbstractXMLRepository<String, Student> {
    /**
     * Class constructor
     * @param filename - numele fisierului
     */
    public StudentXMLRepo(String filename) {
        super(filename);
    }

    /**
     * Extrage informatia despre student dintr-un element XML
     * @param element - XML-ul din care ia datele studentului
     * @return studentul
     */

    @Override
    public Student extractEntity(Element element) {
        String studentId = element.getAttribute("idStudent");
        NodeList nods = element.getChildNodes();
        String nume =element.getElementsByTagName("nume")
                .item(0)
                .getTextContent();
        String grupa =element.getElementsByTagName("grupa")
                .item(0)
                .getTextContent();
        String email =element.getElementsByTagName("email")
                .item(0)
                .getTextContent();

        return new Student(studentId, nume, Integer.parseInt(grupa), email);
    }

    @Override
    public Element createElementfromEntity(Document document, Student entity) {
        Element e = document.createElement("student");
        e.setAttribute("idStudent", entity.getID());

        Element nume = document.createElement("nume");
        nume.setTextContent(entity.getNume());
        e.appendChild(nume);

        Element grupa = document.createElement("grupa");
        Integer g=entity.getGrupa();
        grupa.setTextContent(g.toString());
        e.appendChild(grupa);

        Element email = document.createElement("email");
        email.setTextContent(entity.getEmail());
        e.appendChild(email);

        return e;
    }


}
