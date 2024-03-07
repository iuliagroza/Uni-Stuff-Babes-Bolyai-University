package model;

public class Cylinder implements IGeometricObject {
    double heightCm, volumeCm3;

    public Cylinder(double heightCm, double volumeCm3) {
        this.heightCm = heightCm;
        this.volumeCm3 = volumeCm3;
    }

    @Override
    public double getVolumeCm3() {
        return volumeCm3;
    }

    @Override
    public String toString() {
        return String.format("Cylinder having the height of %.2fcm and the volume of %.2fcm3.", heightCm, volumeCm3);
    }
}
