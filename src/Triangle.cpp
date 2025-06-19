#include "Triangle.h"
#include "Plane.h"
#include "Operations.h"
#include <iostream>
#include <vector>

// Construtores
Triangle::Triangle(Point a, Point b, Point c, Vector colour) : a(a), b(b), c(c), colour(colour) {
    setNormal(cross(a-b, c-b));
}

// Print do triangulo no formato <(x1, y1, z1), (x2, y2, z2), (x3, y3, 3z)>
void Triangle::print() {
    std::cout << "<" << 
    "(" << a.getX() << ", " << a.getY() << ", " << a.getZ() << ")" << 
    "(" << b.getX() << ", " << b.getY() << ", " << b.getZ() << ")" << 
    "(" << c.getX() << ", " << c.getY() << ", " << c.getZ() << ")" << 
    std::endl;
}

// Getters
const Point& Triangle::getA() const { return a; }
const Point& Triangle::getB() const { return b; }
const Point& Triangle::getC() const { return c; }
const Vector& Triangle::getColour() const { return colour; }
const Vector& Triangle::getNormal() const { return normal; }

// Setters
void Triangle::setA(Point newA) { a = newA; }
void Triangle::setB(Point newB) { b = newB; }
void Triangle::setC(Point newC) { c = newC; }
void Triangle::setColour(Vector newColour) { colour = newColour; }
void Triangle::setNormal(Vector newNormal) { normal = newNormal; }

// Interseção de um vetor com o triangulo
HitRecord Triangle::hit(const Ray& r) const {
    // Plano da face do triângulo
    Plane p = Plane(getA(), getNormal(), getColour());
    HitRecord rec;
    
    // rec guarda as informações se r intersecta o plano p
    rec = p.hit(r);
    // Se r não intersecta o plano então também não intersecta o triângulo
    if (rec == HitRecord{}) { return {}; }

    // Se r intersecta o plano então temos que verificar se intersecta o triângulo
    // Se alfa, beta e gama forem diferentes de 0 então r intersecta o triângulo
    if (has(rec.hit_point)) {
        return rec;
    } else {
        return {};
    }
}

// Retorna os valores de alfa, beta e gama se o ponto puder ser definido
// a partir dos três vetores dados, isto é, o ponto está dentro do triângulo,
// caso contrário retorna {0, 0, 0}
bool Triangle::has(Point p) const {
    // Sendo P o ponto que queremos testar e A, B e C os vertices do triangulo
    // P = A + (u * (B - A)) + (v * (C - A))
    // P - A = (u * (B - A)) + (v * (C - A))
    // PA = (u * (BA)) + (v * (CA))
    // 
    // Se x = y sendo x e y vetore, então dot(x, z) = dot(y, z)
    // para qualquer vetor z, logo, temos
    // dot(PA, BA) = dot((u * BA), BA) + dot((v * CA), BA) e
    // dot(PA, CA) = dot((u * BA), CA) + dot((v * CA), CA)
    // que é igual a
    // dot(PA, BA) = u * dot(BA, BA) + v * dot(CA, BA) e
    // dot(PA, CA) = u * dot(BA, CA) + v * dot(CA, CA)
    // que são duas equações com duas variáveis.
    // Assim conseguimos achar u e v

    Vector pa = p - getA();
    Vector ba = getB() - getA();
    Vector ca = getC() - getA();
    double paba = dot(pa, ba);
    double baba = dot(ba, ba);
    double caba = dot(ca, ba);
    double paca = dot(pa, ca);
    double baca = dot(ba, ca);
    double caca = dot(ca, ca);

    // Se x = uy + vz e a = ub + vc, então
    // v = (ay - xb) / (yc - zb)
    // u = (x - vz) / y
    double v;
    double u;
    try
    {
        v = (paca * baba - paba * baca) / (baba * caca - caba * baca);
        u = (paba - v * caba) / baba;
    }
    catch(const std::exception& e)
    {
        return false;
    }

    // Para que o ponto esteja dentro do triângulo u e v precisam ser >= 0
    // e u + v <= 1, pois é preciso que o escalar "avance" mas não avance
    // tanto a ponto de sair do triângulo

    if (v < 0) { return false; }
    if (u < 0) { return false; }

    if (v + u <= 1) {
        return true;
    } else {
        return false;
    }
}