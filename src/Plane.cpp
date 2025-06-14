#include "Plane.h"
#include "Point.h"
#include "Vector.h"
#include "Operations.h"

Plane::Plane(Point newPlanePoint, Vector newNormal, Vector newColor) : planePoint(newPlanePoint), normal(newNormal), color(newColor) {}

// Getters
Point Plane::getPlanePoint() const { return planePoint; }
Vector Plane::getNormal() const { return normal; }
Vector Plane::getColor() const { return color; }

// Setters
void Plane::setPlanePoint(Point& newPlanePoint) { planePoint = newPlanePoint ;}
void Plane::setNormal(Vector& newNormal) { normal = newNormal; }
void Plane::setColor(Vector& newColor) { color = newColor; }

bool Plane::hit (const Ray& r) const {
    // Esta função analisa os vetores N normal e vetor D direção do raio
    // ((P - t * D) - Q) * N = 0
    // t = ((Q-P) * n)/(n * d)
    double t = dot(getPlanePoint() - r.origin(), getNormal()) / dot(r.direction(), getNormal());

   /* Vector qp = r.origin() - getPlanePoint() ;
    double qpDotN = dot(qp, getNormal());
    double dDotN = dot(r.direction(), getNormal());*/

    return t >= 0;

    //return (qpDotN == 0.0 && dDotN == 0.0);

    //return r.origin()
    //if (dot(r.direction(), n) == 0) return true;
    //Vector qp = Q - r.origin();
}
