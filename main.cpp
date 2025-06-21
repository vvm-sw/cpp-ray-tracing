#include "src/Hittable.h"
#include "src/Ray.h"
#include "src/Operations.h"
#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Triangle.h"
#include "src/Camera.h"
#include "src/Colormap.cpp"
#include "src/ObjReader.cpp"
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream> // Biblioteca para "File Stream" (fluxo de arquivos)

using namespace std;

// Função que define a cor de fundo
Vector colour(const vector<Hittable*>& l,  const Ray& r) {

    HitRecord closest = HitRecord{
        std::numeric_limits<double>::max(), 
        {0, 0, 0}, {0, 0, 0}, 
        {red(238), green(238), blue(228)}
    };
    double distance;
    HitRecord rec;

    // Itera na lista para verificar os objetos
    for (const auto& obj : l) {
        rec = obj->hit(r);
        if (rec.t != 0) {
            if (rec.t < closest.t) {
                closest = rec;
            }
        }
    }

    return closest.material_color;
}

int main() {
    ofstream exitRGB("img/image.ppm");
    Camera c = Camera(Point(-2.5, 0, 0), Point(1, 0, 0), Vector(0, 1, 0), 1, 200, 100, 90);
    vector<Hittable*> objList;

    // string objFile = "inputs/input.obj";
    string objFile = "inputs/cubo.obj";
    ObjReader objReader(objFile);
    vector<Face> objectFaces = objReader.getFaces();
    vector<vector<Point>> facePointsList = objReader.getFacePoints();

    for (int k = 0; k < objectFaces.size(); ++k) { 
        Face face = objectFaces[k];
        vector<Point> currentFacePoints = facePointsList[k];
        Point p0 = currentFacePoints[0];
        Point p1 = currentFacePoints[1];
        Point p2 = currentFacePoints[2];
        Vector colour = face.kd;
        objList.push_back(new Triangle(p0, p1, p2, colour));
    }

    // Inicio da lista de objetos a serem visto pela câmera
    // objList.clear();
    // objList.push_back(new Plane(Point(0, -3, 0), Vector(0.5, 1, 0), Vector(0, green(255), 0)));
    // objList.push_back(new Plane(Point(0, -6, 0), Vector(0.25, 1, 0), Vector(0, green(255), blue(255))));
    // objList.push_back(new Plane(Point(0, -12, 0), Vector(0, 1, 0), Vector(red(100), green(100), blue(100))));
    // objList.push_back(new Sphere(Point(4, 0, 0), 1, Vector(red(255), 0, 0)));
    // objList.push_back(new Triangle(Point(3, 0, 0), Point(3, 2, 1), Point(3, 2, 4), Vector(0, 0, blue(255))));
    // objList.push_back(new Sphere(Point(2, 1, 1.3), 0.1, Vector(red(255), 0, 0)));
    // objList.push_back(new Triangle(Point(3, 0, 0), Point(3, -2, -1), Point(3, -2, -4), Vector(0, 0, blue(255))));
    // objList.push_back(new Sphere(Point(2, -1, -1.3), 0.1, Vector(red(255), 0, 0)));
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
            int ir = int(255 * col.getX());
            int ig = int(255 * col.getY());
            int ib = int(255 * col.getZ());
            // std::cout << ir << " " << ig << " " << ib << "\n";
            exitRGB << ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}
// test 2