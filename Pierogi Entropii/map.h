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

struct map *allocMapArray(int num);
void freeMapArray(struct map map[], int num);

#endif // !MAP_H