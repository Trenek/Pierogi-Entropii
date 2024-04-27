#include <raylib.h>
#include "player.h"

struct GridTile {
    Vector2 coordinates;
    Color color;
    Texture2D *texture;
    Texture2D *object;
    Texture2D *collectable;
    Texture2D *interactable;
    int interactableID;
    int exit;
};

struct GridTile **allocGridTile(int *width, int *height, Texture2D *texture[], const char *file, int radius, struct player *player);
void freeGrid(struct GridTile **toFree, int height);