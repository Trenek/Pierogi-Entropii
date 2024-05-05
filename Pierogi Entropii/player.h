#include <raylib.h>

#ifndef PLAYER_H
#define PLAYER_H

struct map;

struct player {
    Vector2 coordinates;
    Texture2D *texture;
    int orientation;
    int collectables[16];
};

void movePlayer(struct player *player, struct map map, bool *interact, int *interX, int *interY);

#endif