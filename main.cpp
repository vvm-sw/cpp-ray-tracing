#include "src/Hittable.h"
#include "src/Matrix.h"
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
    string fileName = "letsSee3";
    int camX = -3;
    int camY = -0;
    int camZ = -0;
    // string objFile = "inputs/input.obj";
    string objFile = "inputs/cubo.obj";
    
    ofstream exitRGB("img/" + fileName + ".ppm");
    Camera c = Camera(Point(camX, camY, camZ), Point(1, 0, 0), Vector(0, 1, 0));
    // X -> Para dentro ou para fora da tela
    // y -> Para cima ou para baixo
    // Z -> Para direita ou para esquerda
    vector<Hittable*> objList;
    ObjReader objReader(objFile);
    vector<Face> objectFaces = objReader.getFaces();
    vector<vector<Point>> facePointsList = objReader.getFacePoints();
    
    // ----------------------------------------------------
    // Inicio da lista de objetos a serem visto pela câmera
    Triangle original = Triangle(Point(3, -2, -2), Point(3, -1, -2), Point(3, -2, -1), RED);
    Triangle t1 = original, t2 = original, t3 = original, t4 = original, t5 = original;
    t1.setColour(BLUE);
    t2.setColour(GREEN);
    t3.setColour(MAGENTA);
    t4.setColour(ORANGE);
    t5.setColour(BROWN);
    t1.transfer(Vector(0,4,4));
    t2.transfer(Vector(0,4,0));
    t3.transfer(Vector(0,0,4));
    t4.transfer(Vector(0,2,6));
    t5.transfer(Vector(0,2,-2));

    t1.rotateZ(rad(45));
    t2.rotateX(rad(45));
    t3.rotateY(rad(45));
    t4.rotateAll(rad(45));
    t5.rotateX(rad(45));
    t5.rotateY(rad(45));
    t5.rotateZ(rad(45));
    objList.push_back(&original);
    objList.push_back(&t1);
    objList.push_back(&t2);
    objList.push_back(&t3);
    objList.push_back(&t4);
    objList.push_back(&t5);
    objList.push_back(new Sphere(Point(0,0,0),0.03,Vector(red(255),0,0)));

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
