#pragma once
#include "Ray.h"

class Hittable {
public:
    // O 'virtual' permite que classes filhas reimplementem esta função.
    // O '= 0' a torna uma "função virtual pura", o que significa que
    // a classe Hittable é abstrata e não pode ser instanciada.
    // Classes filhas SÃO OBRIGADAS a implementar esta função.
    virtual bool hit(const Ray& r) const = 0;
    
    // Destrutor virtual é importante para classes base polimórficas
    virtual ~Hittable() = default;
};