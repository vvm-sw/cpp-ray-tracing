#pragma once
#include "Point.h"
#include "Vector.h"
#include <limits>

class Ray;
using namespace std;

struct HitRecord {
    double t = numeric_limits<double>::max(); // Ele nos diz a que distância ao longo do raio a colisão ocorreu. O t menor é sempre a colisão mais próxima.
    Point hit_point{}; // O ponto exato da colisão no espaço 3D.
    Vector normal{}; // Este vetor é perpendicular à superfície e é essencial para calcular sombreamento e reflexos.
    Vector ka{}; // Coeficiente ambiente
    Vector kd{}; // Coeficiente difuso
    Vector ks{}; // Coeficiente especular
    double shininess = 0; // Expoente n para definir o brilho
    double kr = 0; // Coeficiente de reflexão
    double kt = 0; // Coeficiente de transmissão
};

class Hittable {
public:
    Vector ka; // Coeficiente ambiente (pode ser um escalar ou vetor para cor)
    Vector kd; // Coeficiente difuso
    Vector ks; // Coeficiente especular
    double shininess; // Expoente n
    double kr; // Coeficiente de reflexão
    double kt; // Coeficiente de transmissão

    Hittable(Vector ka, Vector kd, Vector ks, double shininess, double kr, double kt) : ka(ka), kd(kd), ks(ks), shininess(shininess), kr(kr), kt(kt) {}

    // O 'virtual' permite que classes filhas reimplementem esta função.
    // O '= 0' a torna uma "função virtual pura", o que significa que
    // a classe Hittable é abstrata e não pode ser instanciada.
    // Classes filhas SÃO OBRIGADAS a implementar esta função.
    virtual HitRecord hit(const Ray& r) const = 0;
    virtual void rotateAll(double angle) = 0;
    virtual void rotateX(double angle) = 0;
    virtual void rotateY(double angle) = 0;
    virtual void rotateZ(double angle) = 0;
    virtual void transfer(Vector distances) = 0;
    virtual void print() {}
    
    virtual const Vector& getka() const { return ka; }
    virtual const Vector& getkd() const { return kd; }
    virtual const Vector& getks() const { return ks; }
    virtual const double& getshininess() const { return shininess; }
    virtual const double& getkr() const { return kr; }
    virtual const double& getkt() const { return kt; }

    // Destrutor virtual é importante para classes base polimórficas
    virtual ~Hittable() = default;
};