package repository;

import exceptions.ObjectException;
import model.IGeometricObject;

public class ArrayRepository implements IRepository {
    IGeometricObject[] objects;
    int size;

    public ArrayRepository(int capacity) throws ObjectException {
        if (capacity <= 0) {
            throw new ObjectException("The capacity of the repository must be positive.");
        }

        objects = new IGeometricObject[capacity];
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public IGeometricObject[] getAllObjects() {
        IGeometricObject[] copy = new IGeometricObject[size];
        System.arraycopy(objects, 0, copy, 0, copy.length);
        return copy;
    }

    @Override
    public void addObject(IGeometricObject object) throws ObjectException {
        if (size == objects.length) {
            throw new ObjectException("Repository size exceeded.");
        }

        objects[size++] = object;
    }

    @Override
    public void removeObject(int position) throws ObjectException {
        if (position >= size || position < 0) {
            throw new ObjectException("Invalid position.");
        }

        for (int i = position; i + 1 < size; i++) {
            objects[i] = objects[i + 1];
        }
        size--;
    }
}