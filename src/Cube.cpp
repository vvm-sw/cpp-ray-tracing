#include "Cube.h"
#include "Triangle.h"
#include "Operations.h"
#include "Ray.h"
#include <iostream>
#include <vector>

// Construtores
Cube::Cube(Point a, Point b, Vector ka, Vector kd, Vector ks, double shininess, double kr, double kt, bool internal) :
    Hittable(ka, kd, ks, shininess, kr, kt),
    a(a),
    b(b),
    internal(internal) { recalculatePoints(); }

    
void Cube::addTriangle(Point a1, Point b1, Point c1) {
    triangles.push_back({a1,b1,c1,getka(),getkd(),getks(),getshininess(),getkr(),getkt()});
}

void Cube::recalculatePoints() {
    Vector left = a - b;
    double edgeLength = left.magnitude();
    Vector forward = cross(left, {0,1,0}).normalized();
    Vector walkToC = forward * edgeLength;
    c = b + walkToC;
    Vector up = cross(forward, left).normalized() * edgeLength;
    d = c + left;
    e = a + up;
    f = b + up;
    g = c + up;
    h = d + up;

    resetTriangles();
    addTriangle(f,b,a);
    addTriangle(a,e,f);
    addTriangle(e,a,d);
    addTriangle(d,h,e);
    addTriangle(h,d,c);
    addTriangle(c,g,h);
    addTriangle(g,c,b);
    addTriangle(b,f,g);
    addTriangle(g,f,e);
    addTriangle(e,h,g);
    addTriangle(b,c,d);
    addTriangle(d,a,b);
    bool test = internal;
    if (internal) {
        for (auto& t : triangles) {
            Point newA = t.getC();
            Point newC = t.getA();
            t.setA(newA);
            t.setC(newC);
            t.recalculateNormal();
        }
    }
}

// Print do triangulo no formato <(x1, y1, z1), (x2, y2, z2), (x3, y3, 3z)>
void Cube::print() {
    std::cout << "<" << 
    "(" << a.getX() << ", " << a.getY() << ", " << a.getZ() << ")" << 
    "(" << b.getX() << ", " << b.getY() << ", " << b.getZ() << ")" << 
    "(" << c.getX() << ", " << c.getY() << ", " << c.getZ() << ")" << 
    "(" << d.getX() << ", " << d.getY() << ", " << d.getZ() << ")" << 
    "(" << e.getX() << ", " << e.getY() << ", " << e.getZ() << ")" << 
    "(" << f.getX() << ", " << f.getY() << ", " << f.getZ() << ")" << 
    "(" << g.getX() << ", " << g.getY() << ", " << g.getZ() << ")" << 
    "(" << h.getX() << ", " << h.getY() << ", " << h.getZ() << ")" << 
    ">" << std::endl;
}

// Getters
const Point& Cube::getA() const { return a; }
const Point& Cube::getB() const { return b; }
const Point& Cube::getC() const { return c; }
vector<Triangle>& Cube::getTriangles() { return triangles; }
const Point Cube::getCentroid() const {
    Vector forward = c - b;
    Vector left = a - b;
    Vector up = cross(forward, left);
    return b + left/2 + up/2 + forward/2;
}

// Interseção de um vetor com o triangulo
HitRecord Cube::hit(const Ray& r) const {
    HitRecord closest{};
    HitRecord rec{};

    // Itera na lista para verificar os objetos
    for (const auto& triangle : triangles) {
        rec = triangle.hit(r);
        if (rec.t < closest.t && rec.t > 0) {
            closest = rec;
        }
    }

    if (closest.t == numeric_limits<double>::max()) {
        return HitRecord{};
    }

    double t_min = 0.00001;
    HitRecord shadowRec;
    Point start = closest.hit_point + closest.normal * t_min;
    Ray shadowRay(start, r.origin() - start);

    bool inShadow = false;
    double lightDistance = (r.origin() - start).magnitude(); 

    for (auto& triangle : triangles) {
        shadowRec = triangle.hit(shadowRay);
        
        // Se o raio de sombra atinge algo que é um hit válido (t > 0)
        // E esse hit está ANTES da luz (shadowRec.t < lightDistance)
        // Então, está em sombra.
        if (shadowRec.t > 0 && shadowRec.t < lightDistance) {
            inShadow = true;
            break;
        }
    }

    if (inShadow) {
        return HitRecord{};
    } else {
        return closest;
    }
}

void Cube::resetTriangles() {
    triangles.clear();
}

void Cube::rotateAll(double angle) {
}

void Cube::rotateX(double angle) {
}

void Cube::rotateY(double angle) {
}

void Cube::rotateZ(double angle) {
}

void Cube::transfer(Vector distances){
}