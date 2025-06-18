#pragma once
#include "Point.h"
#include "Vector.h"
#include "Hittable.h"

class Triangle : public Hittable {
private:
    Point x;
    Point y;
    Point z;
    Vector colour;
    Vector normal;

public:
    // Construtores
    Triangle(Point x, Point y, Point z, Vector colour);

    // Print do triangulo no formato <(x1, y1, z1), (x2, y2, z2), (x3, y3, 3z)>
    void print();

    // Getters
    Point getX() const;
    Point getY() const;
    Point getZ() const;
    Vector getColour() const override;
    Vector getNormal() const;

    // Setters
    void setX(Point newX);
    void setY(Point newY);
    void setZ(Point newZ);
    void setColour(Vector newColour);
    void setNormal(Vector newNormal);

    // Interseção de um vetor com o triangulo
    std::vector<Point> hit(const Ray& r) const override;
};
