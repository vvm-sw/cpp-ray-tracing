#pragma once
#include "Hittable.h"
#include "Point.h"
#include "Vector.h"
#include "Triangle.h"
#include <vector>

using namespace std;

class Cube : public Hittable {
private:
    Point a;
    Point b;
    Point c;
    Point d;
    Point e;
    Point f;
    Point g;
    Point h;
    vector<Triangle> triangles;
    bool internal;
public:
    // Construtores
    Cube(Point a, Point b, Vector ka, Vector kd, Vector ks, double shininess, double kr, double kt, bool internal);

    // Print do cubo no formato <(x1, y1, z1), (x2, y2, z2), (x3, y3, 3z), (x4, y4, z4), (x5, y5, z5), (x6, y6, 6z), (x7, y7, z7), (x8, y8, z8)>
    void print() override;

    // Getters
    const Point& getA() const;
    const Point& getB() const;
    const Point& getC() const;
    const Point& getD() const;
    const Point& getE() const;
    const Point& getF() const;
    const Point& getG() const;
    const Point& getH() const;
    vector<Triangle>& getTriangles();
    const vector<Vector>& getNormals() const;
    const Point getCentroid() const;

    // Setters
    void setA(Point newA);
    void setB(Point newB);
    void setC(Point newC);
    void setD(Point newD);
    void setE(Point newE);
    void setF(Point newF);
    void setG(Point newG);
    void setH(Point newH);
    void recalculatePoints();
    void resetTriangles();
    void addTriangle(Point a1, Point b1, Point c1);

    // Interseção de um vetor com o cubo
    HitRecord hit(const Ray& r) const override;

    void rotateAll(double angle) override;
    void rotateX(double angle) override;
    void rotateY(double angle) override;
    void rotateZ(double angle) override;
    void transfer(Vector distances) override;
};
