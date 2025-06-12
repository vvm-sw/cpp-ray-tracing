#pragma once
#include "Point.h"
#include "Vector.h"
#include <vector>

class Camera {
private:
    Point location;   // Ponto C
    Point pointingAt; // Ponto M
    Vector worldUp;    // Vetor V_up (temporário)
    double distance;    // Distância d
    unsigned int v_res; // Resolução vertical
    unsigned int h_res; // Resolução horizontal
    Vector U, V, W;     // Vetores da base da câmera
    float fieldOfView;

    void calculateBasis();

public:
    // Construtores
    Camera(const Point& location, const Point& pointingAt, const Vector& worldUp, double distance, unsigned int h_res, unsigned int v_res);

    // Getters
    Point getLocation() const;
    Point getPointingAt() const;
    Vector getVectorUp() const;
    double getDistance() const;
    unsigned int getVRes() const;
    unsigned int getHRes() const;
    double getFOV() const;
    Vector getU() const;
    Vector getV() const;
    Vector getW() const;

    // Setters
    void setLocation(const Point& loc);
    void setPointingAt(const Point& point);
    void setVectorUp(const Vector& up);
    void setDistance(double d);
    void setVRes(unsigned int res);
    void setHRes(unsigned int res);
    void setFOV(double fov);
    void setU(const Vector& newU);
    void setV(const Vector& newV);
    void setW(const Vector& newW);
};