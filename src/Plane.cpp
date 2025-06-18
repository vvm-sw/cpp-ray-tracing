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

HitRecord Plane::hit (const Ray& r) const {
    // Esta função analisa os vetores N normal e vetor D direção do raio
    // P -> Origem do raio
    // Q -> Ponto no plano
    // ((P - t * D) - Q) * N = 0
    // t = ((Q-P) * n)/(n * d)

    // Produto escalar de d (direção do raio) com N (normal do plano).
    // Se dDotN == 0, então o raio é paralelo ao plano
    // Se dDotN != 0, então o raio intersecta o plano
    double dDotN = dot(r.direction(), getNormal());
    
    // Vetor da origem do raio até o ponto do plano
    Vector qp = r.origin() - getPlanePoint();

    // Produto escalar de qp (raio->plano) com N (normal do plano).
    // Se qpDotN == 0, então qp é paralelo ao plano e intersecta (infinitas vezes) todo o plano pois o raio está no próprio plano
    // Se qpDotN != 0, então o raio intersecta o plano
    double qpDotN = dot(qp, getNormal());
    if (dDotN == 0) {
        return (qpDotN == 0);
    }
    
    return (qpDotN / dDotN) >= 0;
}
