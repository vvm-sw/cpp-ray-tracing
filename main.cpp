#include "src/Sphere.h"
#include "src/Hittable.h"
#include "src/Camera.h"
#include <iostream>
#include <vector>

using namespace std;

// Função que define a cor de fundo
Vector colour(const vector<Hittable*>& l,  const Ray& r) {

    // Itera na lista para verificar os objetos
    for (const auto& obj : l) {
        if (obj->hit(r)) {
            return Vector(obj->getColor());
        }
    }

    return Vector(0, 0, 0);
}

int main() {
    Camera c = Camera(Point(0, 0, 0), Point(0, 0, 1), Vector(0, 1, 0), 5, 400, 200);
    vector<Hittable*> objList;

    // Inicio da lista de objetos a serem visto pela câmera
    objList.push_back(new Sphere(Point(0,0,-30), 1, Vector(1,0,0)));
    
    // Fim da lista de objetos a serem visto pela câmera

    std::cout << "P3\n" << c.getHRes() << " " << c.getVRes() << "\n255\n";
    for (int j = c.getVRes() - 1; j >= 0; j--) { // de cima para baixo
        for (int i = 0; i < c.getHRes(); i++) { // da esquerda para direita
            // Normaliza as coordenadas do pixel para (u,v) entre 0.0 e 1.0
            double u = double(i) / double(c.getHRes());
            double v = double(j) / double(c.getVRes());
            
            Point target = c.getScreen().lower_left_corner + u * c.getScreen().horizontal + v * c.getScreen().vertical;
            Ray r = Ray(c.getLocation(), target - c.getLocation());
            
            // Calcula a cor para o raio, passando a lista de objetos
            Vector col = colour(objList, r);

            // Converte a cor para o formato de 0 a 255 e imprime
            int ir = int(255.99 * col.getX());
            int ig = int(255.99 * col.getY());
            int ib = int(255.99 * col.getZ());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}