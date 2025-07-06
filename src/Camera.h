#pragma once
#include "Point.h"
#include "Vector.h"

struct Screen {
    Point lower_left_corner;
    Vector horizontal;
    Vector vertical;
};

class Camera {
private:
    Point location;      // Ponto C
    Point pointingAt;    // Ponto M
    Vector worldUp;      // Vetor V_up (temporário)
    double distance;     // Distância d
    unsigned int v_res;  // Resolução vertical
    unsigned int h_res;  // Resolução horizontal
    Vector U, V, W;      // Vetores da base da câmera. W é para trás. U é para direita. V é para cima.
    double fieldOfView;  // Angulo do campo de visão da câmera em graus
    Screen screen;            // Tela de projeção
    double aspectRatio;  // Proporção da tela

    void calculateBasis();

public:
    // Construtores
    Camera(const Point& location, const Point& pointingAt, const Vector& worldUp, double distance = 1, unsigned int h_res = 0, unsigned int v_res = 0, double aspectRatio = 0, double fieldOfView = 0);

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
    Screen getScreen() const;

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
    void createScreen(const Point& p, Vector horizontal, Vector vertical);
};