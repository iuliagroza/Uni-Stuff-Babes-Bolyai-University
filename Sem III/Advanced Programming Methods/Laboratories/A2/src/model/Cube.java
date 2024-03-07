package model;

public class Cube implements IGeometricObject {
    double lengthOfEdgeCm, volumeCm3;

    public Cube(double lengthOfEdgeCm, double volumeCm3) {
        this.lengthOfEdgeCm = lengthOfEdgeCm;
        this.volumeCm3 = volumeCm3;
    }

    @Override
    public double getVolumeCm3() {
        return volumeCm3;
    }

    @Override
    public String toString() {
        return String.format("Cube having edges of %.2fcm and the volume of %.2fcm3.", lengthOfEdgeCm, volumeCm3);
    }
}
