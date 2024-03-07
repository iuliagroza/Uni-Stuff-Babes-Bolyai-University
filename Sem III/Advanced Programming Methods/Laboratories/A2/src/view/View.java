package view;

import controller.Controller;
import exceptions.ObjectException;
import model.Cube;
import model.Cylinder;
import model.IGeometricObject;
import model.Sphere;
import repository.ArrayRepository;
import repository.IRepository;

public class View {
    public static void main(String[] args) throws ObjectException {
        IRepository repository;
        try {
            repository = new ArrayRepository(10);
        } catch (ObjectException e) {
            System.out.println(e.getMessage());
            return;
        }
        Controller controller = new Controller(repository);

        Cube c1 = new Cube(14, 2744);
        Cube c2 = new Cube(1.5, 3.38);
        Cube c3 = new Cube(3.1, 29.79);

        Cylinder cy1 = new Cylinder(8.75, 25.7);

        Sphere s1 = new Sphere(5.76, 800.49);
        Sphere s2 = new Sphere(1.8, 24.43);

        try {
            controller.addObject(c1);
            controller.addObject(c2);
            controller.addObject(c3);

            controller.addObject(cy1);

            controller.addObject(s1);
            controller.addObject(s2);
        } catch (ObjectException e) {
            System.out.println(e.getMessage());
        }

        System.out.println("Initial objects:");
        for (IGeometricObject object : controller.getAllObjects())
            System.out.println(object.toString());
        System.out.println();


        controller.removeObject(0);

        System.out.println("Objects after removal:");
        for (IGeometricObject object : controller.getAllObjects())
            System.out.println(object.toString());
        System.out.println();

        System.out.println("Objects with volume larger than 25cm3:");
        for (IGeometricObject object : controller.filter())
            System.out.println(object.toString());
        System.out.println();
    }
}
