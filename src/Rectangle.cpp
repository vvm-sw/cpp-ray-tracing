#include "Rectangle.h"
#include "Operations.h"
#include "Matrix.h"
#include <iostream>

Rectangle::Rectangle(Point p0_in, double width, double length, Vector col)
    : p0(p0_in), colour(col)
{
    // Largura vai no X
    edgeU = Vector(width, 0, 0);

    // Comprimento vai no Y
    edgeV = Vector(0, length, 0);

    // Normal apontando para +Z
    normal = cross(edgeU, edgeV).normalized();
}

HitRecord Rectangle::hit(const Ray& r) const {
    HitRecord rec;

    double denom = dot(r.direction(), normal);
    if (fabs(denom) < 1e-8)
        return rec; // Raio paralelo

    double t = dot(p0 - r.origin(), normal) / denom;
    if (t <= 0)
        return rec; // Atrás do olho

    Point p = r.point_at_parameter(t);
    Vector d = p - p0;

    double u = dot(d, edgeU.normalized());
    double v = dot(d, edgeV.normalized());

    if (u < 0 || u > edgeU.magnitude() || v < 0 || v > edgeV.magnitude())
        return rec; // Fora do retângulo

    rec.t = t;
    rec.hit_point = p;
    rec.material_color = colour;

    // Normal sempre apontando para fora
    rec.normal = (denom < 0) ? normal : -1 * normal;

    return rec;
}

void Rectangle::rotateX(double angle) {
    Matrix m(4);
    m.buildRotationX(angle);
    p0 = m * p0;
    edgeU = m * edgeU;
    edgeV = m * edgeV;
    normal = cross(edgeU, edgeV).normalized();
}

void Rectangle::rotateY(double angle) {
    Matrix m(4);
    m.buildRotationY(angle);
    p0 = m * p0;
    edgeU = m * edgeU;
    edgeV = m * edgeV;
    normal = cross(edgeU, edgeV).normalized();
}

void Rectangle::rotateZ(double angle) {
    Matrix m(4);
    m.buildRotationZ(angle);
    p0 = m * p0;
    edgeU = m * edgeU;
    edgeV = m * edgeV;
    normal = cross(edgeU, edgeV).normalized();
}

void Rectangle::rotateAll(double angle) {
    Matrix m(4);
    m.buildRotation(angle);
    p0 = m * p0;
    edgeU = m * edgeU;
    edgeV = m * edgeV;
    normal = cross(edgeU, edgeV).normalized();
}

void Rectangle::transfer(Vector d) {
    p0 = p0 + d;
}

void Rectangle::print() const {
    std::cout << "Rectangle <P0: (" << p0.getX() << ", " << p0.getY() << ", " << p0.getZ()
              << "), Width: " << edgeU.magnitude()
              << ", Length: " << edgeV.magnitude()
              << ">" << std::endl;
}
