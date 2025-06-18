#pragma once
#include "Point.h"
#include "Vector.h"
#include "Hittable.h"

class Sphere : public Hittable {
private:
    Point center;
    double radius;
    Vector colour;

public:
    // Construtores
    Sphere(Point center, double radius, Vector colour);

    // Print do vetor no formato (center, radius, <x, y, z>)
    void print();

    // Getters
    Point getCenter() const;
    double getRadius() const;
    virtual Vector getColor() const override;

    // Setters
    void setCenter(Point newCenter);
    void setRadius(double newRadius);
    void setColor(Vector newColor);

    // Interseção de um vetor com a esfera
    virtual bool hit(const Ray& r) const override;
};