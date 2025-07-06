#pragma once
#include "Operations.h"

#define RED Vector(red(255), 0, 0)
#define GREEN Vector(0, green(255), 0)
#define BLUE Vector(0, 0, blue(255))
#define YELLOW Vector(red(255), green(255), 0)
#define CYAN Vector(0, green(255), blue(255))
#define MAGENTA Vector(red(255), 0, blue(255))
#define WHITE Vector(red(255), green(255), blue(255))
#define BLACK Vector(0, 0, 0)
#define GRAY Vector(red(128), green(128), blue(128)) // Cinza médio
#define LIGHT_GRAY Vector(red(192), green(192), blue(192)) // Cinza claro
#define DARK_GRAY Vector(red(64), green(64), blue(64)) // Cinza escuro
#define ORANGE Vector(red(255), green(165), 0)
#define PURPLE Vector(red(128), 0, red(128))
#define BROWN Vector(red(165), green(42), blue(42))