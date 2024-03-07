package controller;

import exceptions.ObjectException;
import model.IGeometricObject;
import repository.IRepository;

public class Controller {
    IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void addObject(IGeometricObject object) throws ObjectException {
        repository.addObject(object);
    }

    public void removeObject(int position) throws ObjectException {
        repository.removeObject(position);
    }

    public IGeometricObject[] filter() {
        IGeometricObject[] copy = new IGeometricObject[repository.getSize()];
        int size = 0;

        for (IGeometricObject object : repository.getAllObjects()) {
            if (object.getVolumeCm3() > 25) {
                copy[size++] = object;
            }
        }

        IGeometricObject[] filteredObjects = new IGeometricObject[size];
        System.arraycopy(copy, 0, filteredObjects, 0, size);
        return filteredObjects;
    }

    public IGeometricObject[] getAllObjects() {
        return repository.getAllObjects();
    }
}