#pragma once
#include "Hittable.h"
#include "Point.h"
#include "Vector.h"

class Plane : public Hittable {
private:
    Point planePoint;
    Vector normal;
    Vector color;

public:
    // Constructor
    Plane(Point newPlanePoint, Vector newNormal, Vector newColor);

    // Getters
    const Point& getPlanePoint() const;
    const Vector& getNormal() const;
    const Vector& getColour() const override;
    
    // Setters
    void setPlanePoint(Point& planePoint);
    void setNormal(Vector& normal);
    void setColor(Vector& color);

    // Hit
    HitRecord hit(const Ray& ray) const override;
};


