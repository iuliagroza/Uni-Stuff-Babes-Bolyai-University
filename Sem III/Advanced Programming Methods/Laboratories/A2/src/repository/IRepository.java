package repository;

import exceptions.ObjectException;
import model.IGeometricObject;

public interface IRepository {
    int getSize();

    IGeometricObject[] getAllObjects();

    void addObject(IGeometricObject object) throws ObjectException;

    void removeObject(int position) throws ObjectException;
}