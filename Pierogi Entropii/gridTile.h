#ifndef GRIDTILE_H
#define GRIDTILE_H

#include <raylib.h>

struct map;
struct player;

struct GridTile {
    Vector2 coordinates;
    Vector2 expectedCoordinates;
    Texture2D *texture;
    Texture2D *object;
    Texture2D *collectable;
    Texture2D *interactable;
    int interactableID;
    int exit;
};

struct GridTile **allocGridTile(int *width, int *height, Texture2D *texture[], const char *file, int radius, struct player *player);
struct GridTile **allocGridTile2(int *width, int *height, Texture2D *texture[], const char *file, int radius, struct player *player);
void changeStage(struct map *map, struct player *player, int interY, int interX, Texture2D *tekstury[], int is[], int *num);
void paint(struct GridTile **grid, int width, int height);
void freeGrid(struct GridTile **toFree, int height);

#endif