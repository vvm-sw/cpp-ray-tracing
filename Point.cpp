#ifndef POINTHEADER
#define POINTHEADER

/*
Classe de pontos
*/

class point{
    private:
        double x;
        double y;
        double z;
public:

    point() {}
    point(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

#endif