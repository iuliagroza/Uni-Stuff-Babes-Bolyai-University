package repository;

import domain.Nota;
import java.time.LocalDate;
import domain.Nota;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

public class NotaXMLRepo extends AbstractXMLRepository<String, Nota> {

    /**
     * Class constructor
     * @param filename - numele fisierului
     */
    public NotaXMLRepo(String filename) {
        super( filename);
    }

    @Override
    public Element createElementfromEntity(Document document, Nota entity) {
        Element e = document.createElement("nota");

        Element idStudent = document.createElement("idStudent");
        idStudent.setTextContent(entity.getIdStudent());
        e.appendChild(idStudent);

        Element idTema = document.createElement("idTema");
        idTema.setTextContent(entity.getIdTema());
        e.appendChild(idTema);

        Element notaProf = document.createElement("notaProf");
        Double i=entity.getNota();
        notaProf.setTextContent(i.toString());
        e.appendChild(notaProf);

        Element data = document.createElement("dataCurenta");
        LocalDate d = entity.getData();
        data.setTextContent(d.toString());
        e.appendChild(data);

        return e;
    }


    /**
     * Extrage informatia despre nota dintr-un XML
     * @param element - elem XML din care ia datele notei
     * @return nota
     */
    @Override
    public Nota extractEntity(Element element) {
        String id = element.getAttribute("id");
        NodeList nods = element.getChildNodes();

        String studentId =element.getElementsByTagName("idStudent")
                .item(0)
                .getTextContent();

        String temaId =element.getElementsByTagName("idTema")
                .item(0)
                .getTextContent();

        String notaProf =element.getElementsByTagName("notaProf")
                .item(0)
                .getTextContent();


        String data =element.getElementsByTagName("dataCurenta")
                .item(0)
                .getTextContent();

        String[] d = data.split("-");
        LocalDate dat = LocalDate.of(Integer.parseInt(d[0]), Integer.parseInt(d[1]), Integer.parseInt(d[2]));

        return new Nota(id,studentId,temaId,Double.parseDouble(notaProf),dat);
        }
}
