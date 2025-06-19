#pragma once

/*
Classe de vetores.

A saber que:
    - x = componente x
    - y = componente y
    - z = componente z

A classe precisa ser instanciada passando as componentes x, y e z
*/

class Vector{

private:
    double x;
    double y;
    double z;

public:
    // Construtores
    Vector();
    Vector(double x, double y, double z);

    // Print do vetor no formato <x, y, z>
    void print();

    // Getters
    const double& getX() const;
    const double& getY() const;
    const double&  getZ() const;

    // Setters
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);

    // Calcula a magnitude (comprimento) do vetor
    const double magnitude() const;

    // Retorna uma versão normalizada (comprimento 1) do vetor
    const Vector normalized() const;
};
