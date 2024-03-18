package domain;


import repository.HasID;


public class Tema implements HasID<String> {
    private String nrTema;
    private String descriere;
    private int deadline;
    private int primire;

    /**
     *
     * @param nrTema - numarul temei
     * @param descriere - descrierea unei teme
     * @param deadline - deadlineul unei teme
     * @param primire - saptamana de primirea unei teme
     * Class Constructor
     */
    public Tema(String nrTema, String descriere, int deadline, int primire) {
        this.nrTema = nrTema;
        this.descriere = descriere;
        this.deadline = deadline;
        this.primire = primire;
    }

    /**
     * @return descrierea unei teme
     */
    public String getDescriere() {
        return descriere;
    }

    /**
     * modifica descrierea unei teme
     * @param descriere - noua descriere
     */
    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    /**
     * @return deadlineul unei teme
     */
    public int getDeadline() {
        return deadline;
    }

    /**
     * modifica deadlineul unei note
     */
    public void setDeadline(int deadline) {
        this.deadline = deadline;
    }

    /**
     * @return saptamana primirii unei teme
     */
    public int getPrimire() {
        return primire;
    }

    /**
     * modifica saptamana primirii unei teme
     * @param primire - noua saptamana de primire
     */
    public void setPrimire(int primire) {
        this.primire = primire;
    }

    /**
     * @return numarul unei teme
     */
    @Override
    public String getID() {
        return this.nrTema;
    }

    /**
     * schimba numarul unei teme
     * @param nrTema - noul numar al temei
     */
    @Override
    public void setID(String nrTema) {
        this.nrTema = nrTema;
    }

    /**
     * @return un obiect de tip Tema sub forma unui string
     */
    @Override
    public String toString() {
        return nrTema + "," + descriere + "," + deadline + "," + primire;
    }
}
