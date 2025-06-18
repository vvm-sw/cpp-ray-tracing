#pragma once
#include "Ray.h"
#include <vector>

struct HitRecord {
    double t; // Ele nos diz a que distância ao longo do raio a colisão ocorreu. O t menor é sempre a colisão mais próxima.
    Point hit_point; // O ponto exato da colisão no espaço 3D.
    Vector normal; // Este vetor é perpendicular à superfície e é essencial para calcular sombreamento e reflexos.
    Vector material_color; // Cor do material do objeto atingido
};

class Hittable {
public:
    // O 'virtual' permite que classes filhas reimplementem esta função.
    // O '= 0' a torna uma "função virtual pura", o que significa que
    // a classe Hittable é abstrata e não pode ser instanciada.
    // Classes filhas SÃO OBRIGADAS a implementar esta função.
    virtual std::vector<Point> hit(const Ray& r) const = 0;
    virtual Vector getColor() const = 0;
    
    // Destrutor virtual é importante para classes base polimórficas
    virtual ~Hittable() = default;
};