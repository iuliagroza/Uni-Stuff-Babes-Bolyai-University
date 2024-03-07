package model;

public class Sphere implements IGeometricObject {
    double radiusCm, volumeCm3;

    public Sphere(double radiusCm, double volumeCm3) {
        this.radiusCm = radiusCm;
        this.volumeCm3 = volumeCm3;
    }

    @Override
    public double getVolumeCm3() {
        return volumeCm3;
    }

    @Override
    public String toString() {
        return String.format("Sphere having the radius of %.2fcm and the volume of %.2fcm3.", radiusCm, volumeCm3);
    }
}
