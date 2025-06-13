#include "Geometry.h"

// Adição: Ponto + Vetor = Ponto
Point operator+(const Point& p, const Vector& v) {
    return Point(p.getX() + v.getX(), p.getY() + v.getY(), p.getZ() + v.getZ());
}

Point operator+(const Vector& v, const Point& p) {
    return p + v; // Reutiliza a função acima
}

// Subtração: Ponto - Ponto = Vetor
Vector operator-(const Point& p1, const Point& p2) {
    return Vector(p1.getX() - p2.getX(), p1.getY() - p2.getY(), p1.getZ() - p2.getZ());
}

// Adição: Vetor + Vetor = Vetor
Vector operator+(const Vector& v1, const Vector& v2) {
    return Vector(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
}

// Subtração: Vetor - Vetor = Vetor
Vector operator-(const Vector& v1, const Vector& v2) {
    return Vector(v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ());
}

// Multiplicação: Escalar * Vetor = Vetor
Vector operator*(double scalar, const Vector& v) {
    return Vector(scalar * v.getX(), scalar * v.getY(), scalar * v.getZ());
}

Vector operator*(const Vector& v, double scalar) {
    return scalar * v; // Reutiliza a função acima
}

// Produto Vetorial entre vetores
Vector cross(const Vector& v1, const Vector& v2) {
    double crossX = v1.getY() * v2.getZ() - v1.getZ() * v2.getY();
    double crossY = v1.getZ() * v2.getX() - v1.getX() * v2.getZ();
    double crossZ = v1.getX() * v2.getY() - v1.getY() * v2.getX();
    return Vector(crossX, crossY, crossZ);
}

// Divisão por escalar 
Vector operator/(const Vector& v, double t) {
    return Vector(v.getX() / t, v.getY() / t, v.getZ() / t);
}