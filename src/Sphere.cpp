#include "Sphere.h"
#include "Operations.h"
#include "Ray.h"
#include <iostream>
#include <cmath>

// Construtores
Sphere::Sphere(Point center, double radius, Vector ka, Vector kd, Vector ks, double shininess, double kr, double kt) :
    Hittable(ka, kd, ks, shininess, kr, kt),
    center(center),
    radius(radius)
    {}

// Print do vetor no formato (center, radius, <x, y, z>)
void Sphere::print() {
    std::cout << "(" << center.getX() << ", " << center.getY() << ", " << center.getZ() << ")" 
    << ", " << radius << std::endl;
}

// Getters
const Point& Sphere::getCenter() const { return center; }
const double& Sphere::getRadius() const { return radius; }

// Setters
void Sphere::setCenter(Point newCenter) { center = newCenter; }
void Sphere::setRadius(double newRadius) { radius = newRadius; }

// Interseção de um vetor com a esfera
HitRecord Sphere::hit(const Ray& r) const {
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
    // Se o discriminante for < 0 então não temos raízes reais, ou seja não há interseção
    if (discriminant < 0) { return {}; }
    
    HitRecord rec;
    // t1 e t2 são os valores de t que satisfazem a(s) interseção(ões)
    double t1;
    // Um pequeno epsilon (t_min) para evitar artefatos de precisão (z-fighting)
    // Epsilon é importante para evitar que objetos "encostando" na câmera ou um no outro
    // causem problemas de interseção.
    double t_min = 0.001;
    // Se o discriminante for = 0 então temos apenas uma raíz, ou seja há interseção
    if (discriminant == 0) {
        t1 = (-b) / (2 * a);
        if (t1 > t_min) {
            rec.t = t1;
            rec.hit_point = r.origin() + (rec.t * r.direction());
            rec.normal = (rec.hit_point - getCenter()).normalized();
            rec.ka = getka();
            rec.ks = getks();
            rec.kd = getkd();
            rec.kr = getkr();
            rec.kt = getkt();
            rec.shininess = getshininess();
        } else {
            return {};
        }
    } else {
        // Se o discriminante for > 0 então temos duas raízes, ou seja há interseção
        double root = sqrt(discriminant);
        double t2 = t1 = root;
        t1 = (-b + t1) / (2 * a);
        t2 = (-b - t2) / (2 * a);
        double tres = t1 < t2 ? t1 : t2;
        if (tres > t_min) {
            rec.t = tres;
            rec.hit_point = r.origin() + (rec.t * r.direction());
            rec.normal = (rec.hit_point - getCenter()).normalized();
            rec.ka = getka();
            rec.ks = getks();
            rec.kd = getkd();
            rec.kr = getkr();
            rec.kt = getkt();
            rec.shininess = getshininess();
        } else {
            return {};
        }
    }
    
    return rec;
}

void Sphere::rotateAll(double angle) {}
void Sphere::rotateX(double angle) {}
void Sphere::rotateY(double angle) {}
void Sphere::rotateZ(double angle) {}
void Sphere::transfer(Vector distances) {}