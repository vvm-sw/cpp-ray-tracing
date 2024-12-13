#ifndef OBJREADERHEADER
#define OBJREADERHEADER

/*
Classe leitora de arquivos .obj. Onde o arquivo contém os vários pontos, normais e faces do objeto. No projeto 
trabalhamos com faces triangulares, ou seja, uma face consiste em 3 pontos. 

No arquivo .obj, temos:
    - v = pontos
    - vn = normais
    - vt = texturas
    - f = faces


Obs: -  Para fins de abstração, as normais de cada ponto são ignoradas e assumimos apenas uma normal para cada face. 
     -  As texturas também são ignoradas.

Caso sintam necessidade, podem editar a classe para obter mais informações.
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Vector.cpp"
#include "Point.cpp"
#include "Colormap.cpp"


struct Face {
    int verticeIndice[3];
    int normalIndice[3];
    vetor cor;
    vetor ka;
    vetor kd;
    vetor ks;
    vetor ke;
    double ns;
    double ni;
    double d;

    Face() {
        for (int i = 0; i < 3; ++i) {
            verticeIndice[i] = 0;
            normalIndice[i] = 0;
        }
        cor = vetor(); // Assumindo que `vetor` tem um construtor padrão
        ka = vetor();
        kd = vetor();
        ks = vetor();
        ke = vetor();
        ns = 0.0;
        ni = 0.0;
        d = 0.0;
    }
};

class objReader {

private:
    std::ifstream file;
    std::vector<point> vertices;
    std::vector<vetor> normals;
    std::vector<Face> faces;
    std::vector<std::vector<point>> facePoints;
    MaterialProperties curMaterial; // Propriedades do material atual
    colormap cmap;

public:
    objReader(std::string filename, colormap& cmap) : cmap(cmap) {

        // Abre o arquivo
        file.open(filename);
        if (!file.is_open()) {
            std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
            return;
        }

        // Leitura do arquivo
        std::string line, mtlfile, colorname, filename_mtl;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "mtllib") {
                iss >> filename_mtl;
                std::string filename_mtl_path = filename.replace(filename.length() - 3, 3, "mtl");
                cmap = colormap(filename_mtl_path);
            } else if (prefix == "usemtl") {
                iss >> colorname;
                curMaterial = cmap.getMaterialProperties(colorname);
            } else if (prefix == "v") {
                double x, y, z;
                iss >> x >> y >> z;
                vertices.emplace_back(x, y, z);
            } else if (prefix == "vn") {
                double x, y, z;
                iss >> x >> y >> z;
                normals.emplace_back(x, y, z);
            } else if (prefix == "f") {
                Face face;
                char slash;
                for (int i = 0; i < 3; ++i) {
                    int _;
                    iss >> face.verticeIndice[i] >> slash >> _ >> slash >> face.normalIndice[i];
                    face.cor = curMaterial.kd;
                    face.ka = curMaterial.ka;
                    face.kd = curMaterial.kd;
                    face.ks = curMaterial.ks;
                    face.ke = curMaterial.ke;
                    face.ns = curMaterial.ns/250.0;
                    face.ni = curMaterial.ni;
                    face.d = curMaterial.d;
                    face.verticeIndice[i]--;
                    face.normalIndice[i]--;
                }
                faces.push_back(face);
            }

        }
        for (const auto& face : faces) {
            std::vector<point> points = {
                vertices[face.verticeIndice[0]],
                vertices[face.verticeIndice[1]],
                vertices[face.verticeIndice[2]]
            };
            facePoints.push_back(points);
        }

        file.close();
    }

    // Getters

    // Método para retornar as coordenadas dos pontos das faces
    std::vector<std::vector<point>> getFace() {
        return facePoints;
    }

    // Método para retornar a cor do material (Coeficiente de difusão)
    vetor getKd() {
        return curMaterial.kd;
    }

    // Método para retornar a cor do ambiente
    vetor getKa() {
        return curMaterial.ka;
    }

    // Método para retornar o coeficiente especular (Refletência)
    vetor getKe() {
        return curMaterial.ke;
    }

    // Método para retornar o coeficiente de brilho
    double getNs() {
        return curMaterial.ns;
    }

    // Método para retornar o coeficiente de opacidade
    double getNi() {
        return curMaterial.ni;
    }

    // Método para retornar as coordenadas dos pontos
    std::vector<point> getVertices() {
        return vertices;
    }


    // Emite um output no terminal para cada face, com seus respectivos pontos (x, y, z)
    void print_faces() {
        int i = 0;
        for (const auto& face : facePoints) {
            i++;
            std::clog << "Face " << i << ": ";
            for (const auto& point : face) {
                std::cout << "(" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ")";
            }
            std::clog << std::endl;
        }
    }
};

#endif