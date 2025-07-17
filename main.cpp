#include "src/Hittable.h"
#include "src/Matrix.h"
#include "src/Ray.h"
#include "src/Operations.h"
#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Triangle.h"
#include "src/Rectangle.h"
#include "src/Camera.h"
#include "src/Light.h"
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
Vector simpleColour(const vector<Hittable*>& l,  const Ray& r) {

    HitRecord closest = HitRecord{
        std::numeric_limits<double>::max(),
        {0,0,0}, {0,0,0}, {0,0,0},
        {red(238), green(238), blue(228)}, // Cor de fundo padrão
        {0,0,0}, 0.0
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

    return closest.kd;
}

Vector phongColour(const vector<Hittable*>& objList, const vector<Light::PontualLight*>& pontualLights, const Light::EnvLight& ambientLight, const Point& cameraLocation, const Ray& r) {

    // t_min é crucial para raios de sombra e evitar z-fighting.
    const double t_min = 0.001; 

    HitRecord closest = HitRecord{
        std::numeric_limits<double>::max(),
        {0,0,0}, {0,0,0}, {0,0,0},
        {red(238), green(238), blue(228)}, // Cor de fundo padrão
        {0,0,0}, 0.0
    };
    HitRecord current_rec;
    HitRecord shadowRec;

    // Itera na lista para verificar os objetos
    for (const auto& obj : objList) {
        current_rec = obj->hit(r); 
        
        if (current_rec.t > 0 && current_rec.t < closest.t) {
            closest = current_rec;
        }
    }

    // Se closest.t ainda for o valor máximo, significa que nenhum objeto foi atingido (ou todos tiveram t <= 0).
    // Ou seja, a cor de fundo deve ser retornada.
    if (closest.t == std::numeric_limits<double>::max()) {
        return closest.kd; // Retorna a cor de fundo
    }

    Vector finalColor = Vector(0, 0, 0);

    // 1. Componente Ambiente (ka * Ia)
    finalColor = finalColor + (closest.ka * ambientLight.getColour());

    // 2. Componente Difusa e Especular para cada luz pontual
    for (const auto& light : pontualLights) {
        Vector lightColor = light->getColour();     // I_Li
        Point lightLocation = light->getLocation();

        Vector L = (lightLocation - closest.hit_point).normalized(); // Vetor da luz. É um vetor unitário que aponta da superfície para a fonte de luz.
        Vector N = closest.normal;  // Vetor normal da superfície. É um vetor unitário que aponta para fora da superfície no ponto que está sendo iluminado.
        Vector V = (cameraLocation - closest.hit_point).normalized(); // Vetor de visão. É o vetor unitário que aponta da superfície para a câmera (o observador).

        // 3. Gerenciamento de Sombras
        // Adiciona um pequeno offset à origem do raio de sombra para evitar auto-sombreamento
        // É CRUCIAL que o raio de sombra não comece exatamente no ponto de interseção para evitar "acne" de sombra.
        Ray shadowRay(closest.hit_point + N * t_min, L); // Usando t_min para offset da origem

        bool inShadow = false;
        double lightDistance = (lightLocation - closest.hit_point).magnitude(); 

        for (const auto& shadowObj : objList) {
            shadowRec = shadowObj->hit(shadowRay);
            
            // Se o raio de sombra atinge algo que é um hit válido (t > 0)
            // E esse hit está ANTES da luz (shadowRec.t < lightDistance)
            // Então, está em sombra.
            if (shadowRec.t > 0 && shadowRec.t < lightDistance) {
                inShadow = true;
                break;
            }
        }

        if (!inShadow) {
            // Componente Difusa: I_Li * k_d * (N . L_i)
            double NdotL = std::max(0.0, dot(N, L));
            Vector diffuse_contrib = closest.kd * NdotL;
            diffuse_contrib = lightColor * diffuse_contrib;
            finalColor = finalColor + diffuse_contrib;

            // Componente Especular: I_Li * k_s * (R_i . V)^n
            Vector R = (2 * dot(N, L) * N - L).normalized();
            double RdotV = std::max(0.0, dot(R, V));
            double shininess_term = pow(RdotV, closest.shininess);
            Vector specular_contrib = closest.ks * shininess_term;
            specular_contrib = lightColor * specular_contrib;
            finalColor = finalColor + specular_contrib;
        }
    }
    
    // Garantir que os componentes RGB não excedam [0,1]
    finalColor.setX(std::min(1.0, finalColor.getX()));
    finalColor.setY(std::min(1.0, finalColor.getY()));
    finalColor.setZ(std::min(1.0, finalColor.getZ()));

    return finalColor;
}

string paintScreen(int i, int j, Camera c, const vector<Hittable*>& objList, const vector<Light::PontualLight*>& pontualLights, const Light::EnvLight& ambientLight) {
    // Normaliza as coordenadas do pixel para (u,v) entre 0.0 e 1.0
    double u = double(i) / double(c.getHRes());
    double v = double(j) / double(c.getVRes());
    
    Point target = c.getScreen().lower_left_corner + (u * c.getScreen().horizontal) + (v * c.getScreen().vertical);
    Ray r = Ray(c.getLocation(), target - c.getLocation());
    
    // Calcula a cor para o raio, passando a lista de objetos
    Vector col = phongColour(objList, pontualLights, ambientLight, c.getLocation(), r);

    // Converte a cor para o formato de 0 a 255 e imprime
    int ir = int(255 * col.getX());
    int ig = int(255 * col.getY());
    int ib = int(255 * col.getZ());

    return (to_string(ir) + " " + to_string(ig) + " " + to_string(ib));
}

int main() {
    string fileName = "letsSee";
    string objFile = "inputs/cubo.obj";
    Camera c = Camera({0, 0, 0}, {0, 0, -1}, {0, 1, 0});
    // X -> Para direita ou para esquerda
    // y -> Para cima ou para baixo
    // Z -> Para dentro ou para fora da tela



    ofstream exitRGB("img/" + fileName + ".ppm");
    vector<Hittable*> objList;
    vector<Light::PontualLight*> pontualLights;

    // ObjReader objReader(objFile);
    // vector<Face> objectFaces = objReader.getFaces();
    // vector<vector<Point>> facePointsList = objReader.getFacePoints();

    // ----------------------------------------------------
    // Inicio da lista de luzes

    Light::EnvLight ambientLight = Light::EnvLight(Vector(0.5, 0.5, 0.5));
    Light::PontualLight l1 = Light::PontualLight({0, 0.5, -2}, {1,1,1}); // Luz branca forte acima
    Light::PontualLight l2 = Light::PontualLight({-1.5, -0.5, -1.7}, {0.7, 0.7, 0.7}); // Outra luz, mais fraca
    Light::PontualLight l3 = Light::PontualLight({2, 0.5, -2.3}, {1,1,1});
    // Light::PontualLight l4 = Light::PontualLight({0, 0, -2}, {1,1,1});
    pontualLights.push_back(&l1);
    pontualLights.push_back(&l2);
    // pontualLights.push_back(&l3);
    // pontualLights.push_back(&l4);

    // Fim da lista de luzes
    // ----------------------------------------------------

    // ----------------------------------------------------
    // Inicio da lista de objetos
    // Triângulo (AZUL) - um pouco brilhante
    Triangle t = Triangle({-0.6, -0.4, -3}, {0.4, -0.4, -3}, {0.4, 0.4, -3}, BLUE, BLUE, {0, 0, 0}, 16);

    // Esfera (VERMELHA)
    Sphere s = Sphere({0,0,-3}, 0.3, RED/1.5, RED, WHITE, 16);
    Sphere s1 = Sphere({-2,0.5,-3}, 0.5, PURPLE, LIGHT_GRAY, BLACK, 8);
    Sphere s2 = Sphere({2,0.5,-3}, 0.5, BLACK, DARK_GRAY, WHITE, 100);
    Sphere sl1 = Sphere(l1.getLocation()+Vector{0,0.05,0}, 0.02, YELLOW, YELLOW, YELLOW, 500);
    Sphere sl2 = Sphere(l2.getLocation()+Vector{0,0.05,0}, 0.02, YELLOW, YELLOW, YELLOW, 500);
    Sphere sl3 = Sphere(l3.getLocation()+Vector{0,0.05,0}, 0.02, YELLOW, YELLOW, YELLOW, 500);

    // Retângulo Eixo X (VERMELHO)
    Rectangle axisX = Rectangle({-1.7,-1,-2}, 0.03, 0.6, {0.7, 0, 0}, RED, {0, 0, 0}, 32);

    // Retângulo Eixo Y (VERDE)
    Rectangle axisY = Rectangle({-1.7,-1,-2}, 0.03, 0.6, {0, 0.7, 0}, GREEN, {0, 0, 0}, 32);

    // Retângulo Eixo Z (AZUL)
    Rectangle axisZ = Rectangle({-1.7,-1,-2}, 0.03, 0.6, {0, 0, 0.7}, BLUE, {0, 0, 0}, 32);

    objList.push_back(&t);
    objList.push_back(&s);
    objList.push_back(&s1);
    objList.push_back(&s2);
    objList.push_back(&sl1);
    objList.push_back(&sl2);
    // objList.push_back(&sl3);
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
    
    // Fim da lista de objetos
    // ----------------------------------------------------
    
    exitRGB << "P3\n" << c.getHRes() << " " << c.getVRes() << "\n255\n";
    for (int j = c.getVRes() - 1; j >= 0; j--) { // de cima para baixo
        for (int i = 0; i < c.getHRes(); i++) { // da esquerda para direita
            exitRGB << paintScreen(i, j, c, objList, pontualLights, ambientLight) << "\n";
        }
    }

    exitRGB.close();
    cout << "Arquivo '" << fileName << ".ppm' criado na pasta 'img' com sucesso!" << endl;
    return 0;
}
