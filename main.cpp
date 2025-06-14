#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Hittable.h"
#include "src/Camera.h"
#include <iostream>
#include <vector>
#include <fstream> // Biblioteca para "File Stream" (fluxo de arquivos)

using namespace std;

// Função que define a cor de fundo
Vector colour(const vector<Hittable*>& l,  const Ray& r) {

    // Itera na lista para verificar os objetos
    for (const auto& obj : l) {
        if (obj->hit(r)) {
            return Vector(obj->getColor());
        }
    }

    return Vector(238,238,228);
}

int main() {
    ofstream exitRGB("imagem.ppm");

    Camera c = Camera(Point(0, 0, 0), Point(1, 0, 0), Vector(0, 1, 0), 1, 400, 200, 90);
    vector<Hittable*> objList;

    // Inicio da lista de objetos a serem visto pela câmera
    objList.push_back(new Sphere(Point(0, 2, 0), 1, Vector(255, 0, 0)));
    objList.push_back(new Plane(Point(0, -1, 0), Vector(0, 1, 0), Vector(0, 255, 0)));
    
    // Fim da lista de objetos a serem visto pela câmera

    // std::cout << "P3\n" << c.getHRes() << " " << c.getVRes() << "\n255\n";
    exitRGB << "P3\n" << c.getHRes() << " " << c.getVRes() << "\n255\n";
    for (int j = c.getVRes() - 1; j >= 0; j--) { // de cima para baixo
        for (int i = 0; i < c.getHRes(); i++) { // da esquerda para direita
            // Normaliza as coordenadas do pixel para (u,v) entre 0.0 e 1.0
            double u = double(i) / double(c.getHRes());
            double v = double(j) / double(c.getVRes());
            
            Point target = c.getScreen().lower_left_corner + (u * c.getScreen().horizontal) + (v * c.getScreen().vertical);
            Ray r = Ray(c.getLocation(), target - c.getLocation());
            
            // Calcula a cor para o raio, passando a lista de objetos
            Vector col = colour(objList, r);

            // Converte a cor para o formato de 0 a 255 e imprime
            int ir = int(col.getX());
            int ig = int(col.getY());
            int ib = int(col.getZ());
            // std::cout << ir << " " << ig << " " << ib << "\n";
            exitRGB << ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}