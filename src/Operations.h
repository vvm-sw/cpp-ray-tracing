#pragma once
#include "Point.h"
#include "Vector.h"
#include "Hittable.h"
#include "Matrix.h"

// Adição: Ponto + Vetor = Ponto
Point operator+(const Point& p, const Vector& v);
Point operator+(const Vector& v, const Point& p);

// Subtração: Ponto - Vetor = Vetor
Point operator-(const Point& p, const Vector& v);
Point operator-(const Vector& v, const Point& p);

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
double dot(const Vector& v1, const Vector& v2);

// Comparação entre dois vetores
bool operator==(const Vector& a, const Vector& b);
bool operator!=(const Vector& a, const Vector& b);

// Comparação entre dois pontos
bool operator==(const Point& a, const Point& b);
bool operator!=(const Point& a, const Point& b);

// Comparação entre dois HitRecord
bool operator==(const HitRecord& a, const HitRecord& b);
bool operator!=(const HitRecord& a, const HitRecord& b);

// Retorna o valor do vermelho normalizado (entre 0 e 1)
double red(const double& a);

// Retorna o valor do verde normalizado (entre 0 e 1)
double green(const double& a);

// Retorna o valor do azul normalizado (entre 0 e 1)
double blue(const double& a);

// Matriz * Vetor = Vetor
Vector operator*(const Matrix& m, const Vector& v);
// Vetor * Matriz = Vetor
Vector operator*(const Vector& v, const Matrix& m);

// Matriz * Ponto = Ponto
Point operator*(const Matrix& m, const Point& p);
// Ponto * Matriz = Ponto
Point operator*(const Point& p, const Matrix& m);

// Matriz * Matriz = Matriz
Matrix operator*(const Matrix& m1, const Matrix& m2);

// Retorna em radianos o ângulo entrado (ang)
double rad(double ang);

// Multiplicação componente a componente de um vetor
Vector operator*(const Vector& v1, const Vector& v2);

// Soma de vetores com operador curto - não sei como se chama isso, hehe
void operator+=(Vector& a, const Vector& b);