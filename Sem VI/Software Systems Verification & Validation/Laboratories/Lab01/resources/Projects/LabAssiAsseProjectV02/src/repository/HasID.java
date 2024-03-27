package repository;

public interface HasID<ID> {

    /**
     *
     * @return id-ul unui obiect
     */
    ID getID();

    /**
     * Modifica id-ul unul obiect
     * @param id - noul id
     */
    void setID(ID id);
}