#ifndef VECTORHEADER
#define VECTORHEADER
#include <iostream>
#include <math.h>

/*
Classe de vetores
*/

class vetor{
    private:
        double x;
        double y;
        double z;
    
    public:
    vetor() {}
    vetor(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

#endif