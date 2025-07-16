#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Hittable.h"
#include "Ray.h"
#include "Point.h"
#include "Vector.h"

class Rectangle : public Hittable {
private:
    Point p0;        // Canto inicial
    Vector edgeU;    // Vetor da largura (X)
    Vector edgeV;    // Vetor do comprimento (Y)
    Vector normal;   // Normal da face
    Vector colour;   // Cor

public:
    Rectangle(Point p0, double width, double length, Vector colour);

    virtual HitRecord hit(const Ray& r) const override;
    virtual void rotateX(double angle) override;
    virtual void rotateY(double angle) override;
    virtual void rotateZ(double angle) override;
    virtual void rotateAll(double angle) override;
    virtual void transfer(Vector d) override;

    void print() const ;

    const Vector& getColour() const { return colour; }
};

#endif
