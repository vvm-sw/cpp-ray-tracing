#include "src/Hittable.h"
#include "src/Matrix.h"
#include "src/Ray.h"
#include "src/Operations.h"
#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Triangle.h"
#include "src/Rectangle.h"
#include "src/Camera.h"
#include "src/Colormap.cpp"
#include "src/ObjReader.cpp"
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include "src/Colours.h"

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

string paintScreen(int i, int j, Camera c, vector<Hittable*> objList) {
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

    return (to_string(ir) + " " + to_string(ig) + " " + to_string(ib));
}

int main() {
    string fileName = "letsSee";
    string objFile = "inputs/cubo.obj";
    double camX = 0;
    double camY = 0;
    double camZ = 0;
    


    ofstream exitRGB("img/" + fileName + ".ppm");
    Camera c = Camera({camX, camY, camZ}, {0, 0, -1}, {0, 1, 0});
    vector<Hittable*> objList;
    // X -> Para direita ou para esquerda
    // y -> Para cima ou para baixo
    // Z -> Para dentro ou para fora da tela
    // ObjReader objReader(objFile);
    // vector<Face> objectFaces = objReader.getFaces();
    // vector<vector<Point>> facePointsList = objReader.getFacePoints();
    
    // ----------------------------------------------------
    // Inicio da lista de objetos a serem visto pela câmera
    Triangle t = Triangle({-0.6, -0.4, -3}, {0.4, -0.4, -3}, {0.4, 0.4, -3}, BLUE);
    Sphere s = Sphere({0,0,-3},0.3,RED);
    Rectangle axisX = Rectangle({-1.7,-1,-2}, 0.03, 0.6, RED);
    Rectangle axisY = Rectangle({-1.7,-1,-2}, 0.03, 0.6, GREEN);
    Rectangle axisZ = Rectangle({-1.7,-1,-2}, 0.03, 0.6, BLUE);
    objList.push_back(&t);
    objList.push_back(&s);
    objList.push_back(&axisX);
    objList.push_back(&axisZ);
    objList.push_back(&axisY);
    t.rotateZ(rad(45));
    t.rotateX(rad(45));
    t.rotateY(rad(45));
    axisZ.rotateX(rad(90));
    axisX.rotateZ(rad(90));
    axisZ.transfer({-0.178,-0.39,-0.5});
    axisX.transfer({0.285,-0.29,0});

    // for (int k = 0; k < objectFaces.size(); ++k) { 
    //     Point p0 = facePointsList[k][0];
    //     Point p1 = facePointsList[k][1];
    //     Point p2 = facePointsList[k][2];
    //     objList.push_back(new Triangle(p0, p1, p2, objectFaces[k].kd));
    // }
    
    // Fim da lista de objetos a serem visto pela câmera
    // ----------------------------------------------------
    
    exitRGB << "P3\n" << c.getHRes() << " " << c.getVRes() << "\n255\n";
    for (int j = c.getVRes() - 1; j >= 0; j--) { // de cima para baixo
        for (int i = 0; i < c.getHRes(); i++) { // da esquerda para direita
            exitRGB << paintScreen(i, j, c, objList) << "\n";
        }
    }

    exitRGB.close();
    cout << "Arquivo '" << fileName << ".ppm' criado na pasta 'img' com sucesso!" << endl;
    return 0;
}
