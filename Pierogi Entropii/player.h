#include <raylib.h>

#ifndef PLAYER_H
#define PLAYER_H

struct player {
    Vector2 coordinates;
    Texture2D *texture;
    int orientation;
    int collectables[16];
};

#endif