#pragma once
#include "Point.h"
#include "Hittable.h"

class Triangle : public Hittable {
private:
    Point x;
    Point y;
    Point z;

public:
    // Construtores
    Triangle(Point x, Point y, Point z);

    // Print do triangulo no formato <(x1, y1, z1), (x2, y2, z2), (x3, y3, 3z)>
    void print();

    // Getters
    Point getX() const;
    Point getY() const;
    Point getZ() const;

    // Setters
    void setX(Point newX);
    void setY(Point newY);
    void setZ(Point newZ);

    // Interseção de um vetor com o triangulo
    virtual bool hit(const Ray& r) const override;
};
