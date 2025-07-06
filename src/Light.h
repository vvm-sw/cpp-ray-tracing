#include "Point.h"
#include "Vector.h"

class LightSource {
    Light light;
    Vector envLight;
};

class Light {
    Point position;
    Vector colour;
};