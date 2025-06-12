#include "Camera.h"
#include "Geometry.h"

// Construtores
Camera::Camera(const Point& location, const Point& pointingAt, const Vector& worldUp, double distance, unsigned int h_res, unsigned int v_res) :
    location(location), pointingAt(pointingAt), worldUp(worldUp), distance(distance), h_res(h_res), v_res(v_res), U(0, 0, 0), V(0, 0, 0), W(0, 0, 0) {
    calculateBasis();
}

// Getters
Point Camera::getLocation() const { return location; }
Point Camera::getPointingAt() const { return pointingAt; }
Vector Camera::getVectorUp() const { return worldUp; }
double Camera::getDistance() const { return distance; }
unsigned int Camera::getVRes() const { return v_res; }
unsigned int Camera::getHRes() const { return h_res; }
double Camera::getFOV() const { return fieldOfView; }
Vector Camera::getU() const { return U; } // Vetor "direita"
Vector Camera::getV() const { return V; } // Vetor "para cima" real
Vector Camera::getW() const { return W; } // Vetor "para trás"

// Setters
void Camera::setLocation(const Point& loc) {
    this->location = loc;
    calculateBasis(); // Recalcula a base sempre que a câmera se move
}
void Camera::setPointingAt(const Point& point) {
    this->pointingAt = point;
    calculateBasis(); // Recalcula a base sempre que a mira muda
}
void Camera::setVectorUp(const Vector& up) { worldUp = up; }
void Camera::setDistance(double d) { distance = d; }
void Camera::setVRes(unsigned int res) { v_res = res; }
void Camera::setHRes(unsigned int res) { h_res = res; }
void Camera::setFOV(double fov) { fieldOfView = fov; }
void Camera::setU(const Vector& newU) { U = newU; } // Vetor "direita"
void Camera::setV(const Vector& newV) { V = newV; } // Vetor "para cima" real
void Camera::setW(const Vector& newW) { W = newW; } // Vetor "para trás"

// O coração da lógica da câmera
void Camera::calculateBasis() {
    // 1. Calcula o vetor W (oposto à direção da mira), conforme a especificação
    W = (location - pointingAt).normalized();

    // 2. Calcula o vetor U (eixo x da câmera, "direita")
    //    U é o produto vetorial do "para-cima" do mundo com W
    U = cross(worldUp, W).normalized();

    // 3. Calcula o vetor V (eixo y da câmera, "para-cima" real)
    //    V é o produto vetorial de W e U para garantir a ortogonalidade
    V = cross(W, U); // Não precisa normalizar, pois U e W já são ortonormais
}