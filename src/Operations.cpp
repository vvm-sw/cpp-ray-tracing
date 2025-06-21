#include "Operations.h"

// Adição: Ponto + Vetor = Ponto
Point operator+(const Point& p, const Vector& v) {
    return Point(p.getX() + v.getX(), p.getY() + v.getY(), p.getZ() + v.getZ());
}

Point operator+(const Vector& v, const Point& p) {
    return p + v; // Reutiliza a função acima
}

// Subtração: Ponto - Vetor = Vetor
Point operator-(const Point& p, const Vector& v) {
    return Point(p.getX() - v.getX(), p.getY() - v.getY(), p.getZ() - v.getZ());
}

Point operator-(const Vector& v, const Point& p) {
    return p - v; // Reutiliza a função acima
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

// Produto Escalar: Vetor * Vetor = Escalar
double dot(const Vector &v1, const Vector &v2) {
    return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
}

// Comparação entre dois pontos
bool operator==(const Point& a, const Point& b) {
    if (a.getX() != b.getX()) { return false; }
    if (a.getY() != b.getY()) { return false; }
    if (a.getZ() != b.getZ()) { return false; }
    return true;
}

bool operator!=(const Point& a, const Point& b) {
    return !(a == b);
}

// Comparação entre dois vetores
bool operator==(const Vector& a, const Vector& b) {
    if (a.getX() != b.getX()) { return false; }
    if (a.getY() != b.getY()) { return false; }
    if (a.getZ() != b.getZ()) { return false; }
    return true;
}

bool operator!=(const Vector& a, const Vector& b) {
    return !(a == b);
}

// Comparação entre dois HitRecord
bool operator==(const HitRecord& a, const HitRecord& b) {
    if (a.t != b.t) { return false; }
    if (a.material_color != b.material_color) { return false; }
    if (a.normal != b.normal) { return false; }
    if (a.hit_point != b.hit_point) { return false; }
    return true;
}

bool operator!=(const HitRecord& a, const HitRecord& b) {
    return !(a == b);
}

// Retorna o valor do vermelho normalizado (entre 0 e 1)
double red(const double& a) {
    return a/255;
}

// Retorna o valor do verde normalizado (entre 0 e 1)
double green(const double& a) {
    return a/255;
}

// Retorna o valor do azul normalizado (entre 0 e 1)
double blue(const double& a) {
    return a/255;
}

// Matriz * Vetor = Vetor
Vector operator*(const Matrix& m, const Vector& v) {
    double vArray[4] {v.getX(), v.getY(), v.getZ(), 1};
    double arrayResult[4] {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arrayResult[i] += m.matrixArray[i][j] * vArray[j];
        }
    }
    return Vector(arrayResult[0], arrayResult[1], arrayResult[2]);
}

// Vetor * Matriz = Vetor
Vector operator*(const Vector& v, const Matrix& m) {
    return m * v;
}

// Matriz * Ponto = Ponto
Point operator*(const Matrix& m, const Point& p) {
    double pArray[4] {p.getX(), p.getY(), p.getZ(), 1};
    double arrayResult[4] {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arrayResult[i] += m.matrixArray[i][j] * pArray[j];
        }
    }
    return Point(arrayResult[0], arrayResult[1], arrayResult[2]);
}

// Ponto * Matriz = Ponto
Point operator*(const Point& p, const Matrix& m) {
    return m * p;
}
