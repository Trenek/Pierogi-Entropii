#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "player.h"
#include "gridTile.h"

struct GridTile **allocGridTile(int *width, int *height, Texture2D *texture[], const char *file, int radius, struct player *player) {
    FILE *f = fopen(file, "r");
    int playerX = 0;
    int playerY = 0;
    fscanf(f, "%i%i", height, width);
    fscanf(f, "%i%i", &playerX, &playerY);
    player->coordinates.x = playerX;
    player->coordinates.y = playerY;
    srand((unsigned int)time(NULL));

    struct GridTile **result = malloc(sizeof(struct GridTile *) * *height);
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < *height) {
        result[i] = malloc(sizeof(struct GridTile) * *width);
        j = 0;
        while (j < *width) {
            fscanf(f, "%i", &k);
            result[i][j] = (struct GridTile){
                .color = { (unsigned char)rand(), (unsigned char)rand(), (unsigned char)rand(), 255 },
                .coordinates = {.x = j * radius, .y = i * radius },
                .object = NULL,
                .texture = texture[0] + k,
                .collectable = NULL
            };

            j += 1;
        }

        i += 1;
    }

    i = 0;
    while (i < *height) {
        j = 0;
        while (j < *width) {
            fscanf(f, "%i", &k);
            if (k != 0) result[i][j].object = texture[1] + k - 1;

            j += 1;
        }
        i += 1;
    }

    i = 0;
    while (i < *height) {
        j = 0;
        while (j < *width) {
            fscanf(f, "%i", &k);
            if (k != 0) result[i][j].interactable = texture[2] + k - 1;

            j += 1;
        }
        i += 1;
    }

    i = 0;
    while (i < *height) {
        j = 0;
        while (j < *width) {
            fscanf(f, "%i", &k);
            if (k != 0) result[i][j].collectable = texture[3] + k - 1;

            j += 1;
        }
        i += 1;
    }

    return result;
}

void freeGrid(struct GridTile **toFree, int height) {
    int i = 0;

    while (i < height) {
        free(toFree[i]);
        i += 1;
    }

    free(toFree);
}