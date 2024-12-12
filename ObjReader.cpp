#ifndef OBJREADERHEADER
#define OBJREADERHEADER

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

    Face() {
        for (int i = 0; i < 3; ++i) {
            verticeIndice[i] = 0;
            normalIndice[i] = 0;
        }
        //cor = vetor(); // Assumindo que `vetor` tem um construtor padrão
    }
};

class objReader {

private:
    std::ifstream file;
    std::vector<point> vertices;
    std::vector<vetor> normals;
    std::vector<Face> faces;
    MaterialProperties curMaterial; // Propriedades do material atual
    colormap cmap;

public:
    objReader(std::string LOCAL_DIR, std::string filename, colormap& cmap) : cmap(cmap) {

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
                    face.cor = curMaterial.ka;
                    face.verticeIndice[i]--;
                    face.normalIndice[i]--;
                }
                faces.push_back(face);
            }
        }

        file.close();
    }

    // Método para retornar as coordenadas dos pontos das faces
    std::vector<std::vector<point>> getFacePoints() {
        std::vector<std::vector<point>> facePoints;
        for (const auto& face : faces) {
            std::vector<point> points = {
                vertices[face.verticeIndice[0]],
                vertices[face.verticeIndice[1]],
                vertices[face.verticeIndice[2]]
            };
            facePoints.push_back(points);
        }
        return facePoints;
    }

    // Getters
    std::vector<point> getVertices() {
        return vertices;
    }

    std::vector<vetor> getNormals() {
        return normals;
    }

    std::vector<Face> getFaces() {
        return faces;
    }
};

#endif