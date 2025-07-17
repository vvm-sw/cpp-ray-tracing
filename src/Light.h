#pragma once

#include "Point.h"
#include "Vector.h"

class Light {
public:
    // Classe para representar uma luz pontual
    class PontualLight {
    private:
        Point location; // Localização da luz no espaço 3D
        Vector colour;  // Cor da luz

    public:
        // Construtor
        PontualLight(const Point& loc, const Vector& col) : location(loc), colour(col) {}

        // Getters
        const Point& getLocation() const { return location; }
        const Vector& getColour() const { return colour; }

        // Setters
        void setLocation(const Point& loc) { location = loc; }
        void setColour(const Vector& col) { colour = col; }
    };

    // Classe para representar uma luz ambiente
    class EnvLight {
    private:
        Vector colour; // Cor da luz

    public:
        // Construtor
        EnvLight(const Vector& col) : colour(col) {}

        // Getters
        const Vector& getColour() const { return colour; }

        // Setters
        void setColour(const Vector& col) { colour = col; }
    };
};