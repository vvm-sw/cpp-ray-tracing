#pragma once
#include <vector>

/*
Classe de pontos.

A saber que:
    - x = componente x
    - y = componente y
    - z = componente z

A classe precisa ser instanciada passando as componentes x, y e z
*/

class Point{
private:
    double x;
    double y;
    double z;

public:
    // Construtores
    Point();
    Point(double x, double y, double z);

    // Print do vetor no formato (x, y, z)
    void print();

    // Getters
    const double& getX() const;
    const double& getY() const;
    const double& getZ() const;

    // Setters
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);
};
