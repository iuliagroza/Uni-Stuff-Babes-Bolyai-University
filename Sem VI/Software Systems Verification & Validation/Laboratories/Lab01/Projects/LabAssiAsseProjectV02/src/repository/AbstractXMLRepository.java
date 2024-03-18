package repository;

import domain.Student;
import validation.ValidationException;
import java.io.*;
import java.util.Optional;

//import javafx.scene.input.DataFormat;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;



public abstract class AbstractXMLRepository<ID, E extends HasID<ID>> extends AbstractCrudRepository<ID, E> implements FileRepository<ID, E> {

    private String filename;
    private DocumentBuilderFactory builderFactory;

    /**
     * Class constructor
     * @param filename - numele fisierului
     */
    AbstractXMLRepository(String filename) {
        this.filename = filename;
        builderFactory=DocumentBuilderFactory.newInstance();
        loadFromFile();

    }


    /**
     * Incarca datele din fisier
     */
    public void loadFromFile(){
        try {
            Document document = DocumentBuilderFactory
                    .newInstance()
                    .newDocumentBuilder()
                    .parse(this.filename);

            Element root = document.getDocumentElement();
            NodeList children = root.getChildNodes();
            for(int i=0; i < children.getLength(); i++) {
                Node entityElement = children.item(i);
                if(entityElement.getNodeType()==Node.ELEMENT_NODE) {
                    E entity = extractEntity((Element)entityElement);
                    super.save(entity);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    /**
     * Creeaza un elemenT XML dintr o  entitate
     * @param document
     * @param entity
     * @return
     */

    public abstract Element createElementfromEntity(Document document, E entity);

    /**
     * Extrage un obiect dintr-un XML
     * @param element - String-ul din care extrage obiectul
     * @return - obiectul
     */


    public abstract E extractEntity(Element element);
    /**
     * Salveaza un obiect
     * @param entity - obiectul pe care il salveaza
     * @return null daca obiectul s-a salvat cu succes sau obiectul daca acesta exista deja in memorie
     */
   @Override
    public E save(E entity) {
       E entity1 = super.save(entity);
       if (entity1 == null) {
            //saveToFile(entity);
       writeToFile();
       }

        return entity1;
   }
    /**
     * Rescrie fisierul cu toate obiectele din memorie
     */

    public void writeToFile(){
        try {
            Document document = DocumentBuilderFactory
                    .newInstance()
                    .newDocumentBuilder()
                    .newDocument();
            Element root  = document.createElement("inbox");
            document.appendChild(root);
            super.findAll().forEach(e->{
                Element elem = createElementfromEntity(document,e);
                root.appendChild(elem);
            });

            //write Document to file
            Transformer transformer = TransformerFactory.
                    newInstance().newTransformer();
            transformer.transform(new DOMSource(document),
                    new StreamResult(this.filename));

        }catch(Exception e){
        e.printStackTrace();
        }
    }

    /**
     * Scrie un obiect nou in fisier
     * @param entity - obiectul pe care il scrie
     */
    public void saveToFile(E entity)
    {
        //E e = super.save(entity);
        //if(e==null){writeToFile();
        //}
        //return e;
    }


    /**
     * Sterge un obiect
     * @param id - id-ul obiectului
     * @return obiectul daca s-a reusit stergerea sau null daca obiectul nu exista
     */
    @Override
    public E delete(ID id) {
        E entity = super.delete(id);
        if(entity != null){
            writeToFile();
        }
        return entity;
    }

    /**
     * Modifica un obiect
     * @param entity - noul obiect
     * @return null daca obiectul a fost modificat sau obiectul, daca acesta nu exista
     */
    @Override
    public E update(E entity) {
        E entity1 = super.update(entity);
        if(entity == null){
            writeToFile();
        }
        return entity1;
    }
}
