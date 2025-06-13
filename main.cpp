#include "src/Ray.h"
#include <iostream>

// Retorna uma versão normalizada do vetor v (comprimento 1)
Vector unit_vector(Vector v) {
    return v.normalized();
}

bool hit_sphere(const Point& center, float radius, const Ray& r) {
    // Esta função resolve a equação quadrática da interseção raio-esfera 
    Vector oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(oc, r.direction());
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c; // Calcula o discriminante
    
    // Se o discriminante > 0, há interseção 
    return (discriminant > 0);
}

// Função que define a cor de fundo
// Ela cria um gradiente azul-branco 
Vector color(const Ray& r) {
    // Se o raio atingir nossa esfera (centro em 0,0,-1, raio 0.5), pinte de vermelho
    if (hit_sphere(Point(0, 0, -1), 0.5, r)) {
        return Vector(1, 0, 0); // Vermelho
    }

    Vector unit_direction = unit_vector(r.direction());
    // Mapeia a componente Y do vetor (-1.0 a 1.0) para t (0.0 a 1.0)
    float t = 0.5 * (unit_direction.getY() + 1.0);
    // Interpolação linear (lerp) entre branco e azul 
    // blended_value = (1-t)*start_value + t*end_value
    return (1.0 - t) * Vector(1.0, 1.0, 1.0) + t * Vector(0.5, 0.7, 1.0);
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // Setup da câmera virtual 
    Vector lower_left_corner(-2.0, -1.0, -1.0); // Canto inferior esquerdo da "tela"
    Vector horizontal(4.0, 0.0, 0.0);           // Largura da "tela"
    Vector vertical(0.0, 2.0, 0.0);             // Altura da "tela"
    Point origin(0.0, 0.0, 0.0);               // Posição do "olho" 

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            // Mapeia o pixel (i,j) para as coordenadas (u,v) na tela (0 a 1)
            double u = double(i) / double(nx);
            double v = double(j) / double(ny);
            
            // Cria um raio que vai da origem para o pixel atual na tela 
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vector col = color(r);

            int ir = int(255.99 * col.getX());
            int ig = int(255.99 * col.getY());
            int ib = int(255.99 * col.getZ());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}