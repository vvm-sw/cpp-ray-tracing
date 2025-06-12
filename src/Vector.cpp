#ifndef VECTORHEADER
#define VECTORHEADER
#include <iostream>
#include <math.h>

/*
Classe de vetores.

A saber que:
    - x = componente x
    - y = componente y
    - z = componente z

A classe precisa ser instanciada passando as componentes x, y e z
*/

class vetor{
    private:
        double x;
        double y;
        double z;

    public:

    //Construtores
    vetor() {}
    vetor(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    //Implemente os métodos de vetores aqui
    vetor multByScalar(double c) {
        vetor resultVetor = vetor(c * this->getX(), c * this->getY(), this->getZ());
        return resultVetor;
    }
    void multByScalarV2(double c) {
        this->x *= c;
        this->y *= c;
        this->z *= c;
    }
    //Print do vetor no formato <x, y, z>
    void print(){
        std::cout << "<" << x << ", " << y << ", " << z << ">" << std::endl;
    }

    //Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};

#endif
