#ifndef MAP_H
#define MAP_H

#include "gridTile.h"

struct map {
    struct GridTile **grid;
    Camera2D camera;
    int height;
    int width;
    Vector2 position;
};

#endif // !MAP_H