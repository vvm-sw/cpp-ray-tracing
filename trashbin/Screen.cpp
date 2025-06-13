#pragma once
#include "Screen.h"

// Construtores
Screen::Screen(double e0, double e1, double e2) {
    e[0] = e0; e[1] = e1; e[2] = e2;
}

// Getters para posições (x,y,z) e cores (r,g,b) 
inline double Screen::x() const { return e[0]; }
inline double Screen::y() const { return e[1]; }
inline double Screen::z() const { return e[2]; }
inline double Screen::r() const { return e[0]; }
inline double Screen::g() const { return e[1]; }
inline double Screen::b() const { return e[2]; }

// Sobrecarga de operadores
inline Screen Screen::operator-() const { return Screen(-e[0], -e[1], -e[2]); } // Negação
inline double Screen::operator[](int i) const { return e[i]; } // Acesso por índice (leitura)
inline double& Screen::operator[](int i) { return e[i]; }      // Acesso por índice (escrita)