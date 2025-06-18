#include "Sphere.h"

// Construtores
Sphere::Sphere(Point center, double radius, Vector colour) : center(center), radius(radius), colour(colour) {}

// Print do vetor no formato (center, radius, <x, y, z>)
void Sphere::print() {
    std::cout << "(" << center.getX() << ", " << center.getY() << ", " << center.getZ() << ")" 
    << ", " << radius << ", " << "<" << colour.getX() << ", " << colour.getY() << ", " << colour.getZ() << ">" << std::endl;
}

// Getters
Point Sphere::getCenter() const { return center; }
double Sphere::getRadius() const { return radius; }
Vector Sphere::getColor() const { return colour; }

// Setters
void Sphere::setCenter(Point newCenter) { center = newCenter; }
void Sphere::setRadius(double newRadius) { radius = newRadius; }
void Sphere::setColor(Vector newColor) { colour = newColor; }

// Interseção de um vetor com a esfera
bool Sphere::hit(const Ray& r) const {
    // // Equação da esfera: (x-c1)² + (y-c2)² + (z-c3)² = r²,
    // Equação da esfera: |P - C|² = r²,
    // onde P é u ponto da superfície da esfera, C é o seu centro e r é o seu raio
    // Equação vetorial da reta: p(t) = o + td,
    // onde p(t) é um ponto qualquer do vetor, o é a origem do vetor, t é um escalar e d é o vetor diretor
    // |(o + td) - C|² = r²
    // |td + OC|² = r² -> |x|² = x . x
    // (td + OC) . (td + OC) = r²
    // (d . d)t² + 2(d . OC)t + (OC . OC) - r² = 0 -> Equação quadrática na forma at²+bt+c=0.
    // Discriminante de uma equação de segundo grau: b² - 4ac.

    Vector oc = r.origin() - getCenter();
    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(r.direction(), oc);
    double c = dot(oc, oc) - (getRadius() * getRadius());
    double discriminant = b * b - 4 * a * c;
    
    // Se o discriminante > 0, há interseção 
    return (discriminant > 0);
}
