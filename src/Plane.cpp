#include "Plane.h"
#include "Point.h"
#include "Vector.h"
#include "Operations.h"

Plane::Plane(Point newPlanePoint, Vector newNormal, Vector newColor) : planePoint(newPlanePoint), normal(newNormal), color(newColor) {}

    // Getters
    Point getPlanePoint() { return planePoint; }
    Vector getNormal() { return normal; }
    Vector GetColor() { return color;}
    // Setters
    void setPlanePoint(Point& nPlanePoint) { planePoint = newPlanePoint ;}
    void setNormal(Vector& newNormal) { normal = newNormal; }
    void setColor(Vector& newColor) { color = newColor; }

    bool hit (const Ray& r) const {
        // Esta função analisa os vetores N normal e vetor D direção do raio
        double t = dot(Q - r.origin(), n)/dot(r.direction(), n);

        Vector qp = Q - r.origin();
        double qpDotN = dot(qp, n);
        double dDotN = dot(r.direction(), n);

        return (qpDotN == 0.0 & dDotN == 0.0);

        //return r.origin()
        //if (dot(r.direction(), n) == 0) return true;
        //Vector qp = Q - r.origin();
    }
