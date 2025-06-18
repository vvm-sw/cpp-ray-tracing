#include "Plane.h"
#include "Point.h"
#include "Vector.h"
#include "Operations.h"

Plane::Plane(Point newPlanePoint, Vector newNormal, Vector newColor) : planePoint(newPlanePoint), normal(newNormal), color(newColor) {}

// Getters
Point Plane::getPlanePoint() const { return planePoint; }
Vector Plane::getNormal() const { return normal; }
Vector Plane::getColour() const { return color; }

// Setters
void Plane::setPlanePoint(Point& newPlanePoint) { planePoint = newPlanePoint ;}
void Plane::setNormal(Vector& newNormal) { normal = newNormal; }
void Plane::setColor(Vector& newColor) { color = newColor; }

std::vector<Point> Plane::hit (const Ray& r) const {
    // Esta função analisa os vetores N normal e vetor D direção do raio
    // P -> Origem do raio
    // Q -> Ponto no plano
    // ((P - t * D) - Q) * N = 0
    // t = ((Q-P) * n)/(n * d)

    
    // ! dot(r.direction(), getNormal()); pode dar 0 !
    double dDotN = dot(r.direction(), getNormal());
    Vector qp = r.origin() - getPlanePoint();
    double qpDotN = dot(qp, getNormal());
    if (dDotN == 0) {
        return (qpDotN == 0);
    };
    
    return (qpDotN / dDotN) >= 0;
}
