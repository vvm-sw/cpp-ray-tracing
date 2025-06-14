#pragma once
#include "Point.h"
#include "Vector.h"
#include "Sphere.h"

// Adição: Ponto + Vetor = Ponto
Point operator+(const Point& p, const Vector& v);

Point operator+(const Vector& v, const Point& p);

// Subtração: Ponto - Ponto = Vetor
Vector operator-(const Point& p1, const Point& p2);

// Adição: Vetor + Vetor = Vetor
Vector operator+(const Vector& v1, const Vector& v2);

// Subtração: Vetor - Vetor = Vetor
Vector operator-(const Vector& v1, const Vector& v2);

// Multiplicação: Escalar * Vetor = Vetor
Vector operator*(double scalar, const Vector& v);
Vector operator*(const Vector& v, double scalar);

// Produto Vetorial entre vetores
Vector cross(const Vector& v1, const Vector& v2);

// Divisão por escalar 
Vector operator/(const Vector& v, double t);

// Produto Escalar: Vetor * Vetor = Escalar
double dot(const Vector &v1, const Vector &v2);

// Interseção de um vetor com a esfera
bool hitSphere(const Sphere& s, Ray& r);