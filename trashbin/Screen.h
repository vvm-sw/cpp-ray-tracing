#pragma once
#include <iostream>

class Screen {
public:
    double e[3]; // Armazena os 3 componentes

    // Construtores
    Screen(double e0, double e1, double e2);

    // Getters para posições (x,y,z) e cores (r,g,b) 
    inline double x() const;
    inline double y() const;
    inline double z() const;
    inline double r() const;
    inline double g() const;
    inline double b() const;

    // Sobrecarga de operadores
    inline Screen operator-() const; // Negação
    inline double operator[](int i) const; // Acesso por índice (leitura)
    inline double& operator[](int i); // Acesso por índice (escrita)
};