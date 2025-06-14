#pragma once
#include "Operations.h"

class Ray {
public:
    Point A; // Origem do raio
    Vector B; // Direção do raio

    Ray(const Point& a, const Vector& b) : A(a), B(b) {}

    Point origin() const { return A; }
    Vector direction() const { return B; }

    // Calcula o ponto ao longo do raio para um parâmetro t
    // A equação é p(t) = A + t * B
    Point point_at(double t) const { return A + (t * B); }
};