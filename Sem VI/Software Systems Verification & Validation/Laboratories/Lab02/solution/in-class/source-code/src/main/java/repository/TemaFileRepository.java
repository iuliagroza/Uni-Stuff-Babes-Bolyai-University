package repository;

import domain.Tema;

public class TemaFileRepository extends AbstractFileRepository<String, Tema> {

    /**
     * Class constructor
     * @param filename - numele fisierului
     */
    public TemaFileRepository(String filename){
        super(filename);
    }

    /**
     * Extrage informatia despre tema dintr-un string
     * @param linie - stringul din care ia datele temei
     * @return tema
     */
    @Override
    public Tema extractEntity(String linie) {
        String[] cuvinte = linie.split(",");
        return new Tema(cuvinte[0], cuvinte[1], Integer.parseInt(cuvinte[2]), Integer.parseInt(cuvinte[3]));
    }
}
