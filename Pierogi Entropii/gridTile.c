#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "player.h"
#include "gridTile.h"
#include "map.h"

#include "createCamera.h"

struct GridTile **allocGridTile(int *width, int *height, Texture2D *texture[], const char *file, int radius, struct player *player) {
    FILE *f = fopen(file, "r");
    int playerX = 0;
    int playerY = 0;
    fscanf(f, "%i%i", height, width);
    fscanf(f, "%i%i", &playerX, &playerY);
    player->coordinates.x = playerX;
    player->coordinates.y = playerY;

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
                .coordinates = {.x = j * radius, .y = i * radius },
                .object = NULL,
                .texture = texture[0] + k,
                .collectable = NULL,
                .interactableID = -1
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
            if (k != 0) {
                result[i][j].interactable = texture[2] + k - 1;
                result[i][j].interactableID = k;
                if (k == 1) {
                    result[i][j].exit = k;
                }
            }

            j += 1;
        }
        i += 1;
    }
    i = 0;
    while (i < *height) {
        j = 0;
        while (j < *width) {
            if (result[i][j].interactableID == 2) {
                fscanf(f, "%i", &k);
                result[i][j].exit = k;
                int m = 0;
                fscanf(f, "%i %i", &k, &m);
                result[i][j].expectedCoordinates = (Vector2){ .x = k, .y = m };
            }

            j += 1;
        }
        i += 1;
    }

    i = 0;
    while (i < *height) {
        j = 0;
        while (j < *width) {
            fscanf(f, "%i", &k);
            if (k != 0) {
                if (result[i][j].interactable == NULL) {
                    result[i][j].collectable = texture[3] + k - 1;
                    result[i][j].exit = k - 1;
                }
                else {
                    result[i][j].exit = k;
                }
            }

            j += 1;
        }
        i += 1;
    }

    return result;
}


struct GridTile **allocGridTile2(int *width, int *height, Texture2D *texture[], const char *file, int radius, struct player *player) {
    FILE *f = fopen(file, "r");
    fscanf(f, "%i%i", height, width);

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
                .coordinates = {.x = j * radius, .y = i * radius },
                .object = NULL,
                .texture = texture[0] + k,
                .collectable = NULL,
                .interactableID = -1
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
            if (k != 0) {
                result[i][j].interactable = texture[2] + k - 1;
                result[i][j].interactableID = k;
                if (k == 1) {
                    result[i][j].exit = k;
                }
            }

            j += 1;
        }
        i += 1;
    }
    i = 0;
    while (i < *height) {
        j = 0;
        while (j < *width) {
            if (result[i][j].interactableID == 2) {
                fscanf(f, "%i", &k);
                result[i][j].exit = k;
                int m = 0;
                fscanf(f, "%i %i", &k, &m);
                result[i][j].expectedCoordinates = (Vector2){ .x = k, .y = m };
            }

            j += 1;
        }
        i += 1;
    }

    i = 0;
    while (i < *height) {
        j = 0;
        while (j < *width) {
            fscanf(f, "%i", &k);
            if (k != 0) {
                if (result[i][j].interactable == NULL) {
                    result[i][j].collectable = texture[3] + k - 1;
                    result[i][j].exit = k - 1;
                }
                else {
                    result[i][j].exit = k;
                }
            }

            j += 1;
        }
        i += 1;
    }

    return result;
}

void changeStage(struct map *map, struct player *player, int interY, int interX, Texture2D *tekstury[], int is[], int *num) {
    int radius = 16;
    int width = 0;
    int height = 0;

    map[*num].position = player->coordinates;
    map[*num].camera = createCamera(map[*num].width, map[*num].height, radius);
    player->coordinates = map[*num].grid[interY][interX].expectedCoordinates;
    *num = map[*num].grid[interY][interX].exit;
    if (is[*num] == 0) {
        is[*num] = 1;
        printf("%s", TextFormat("stage/%i.txt", *num));
        struct GridTile **grid = allocGridTile2(&width, &height, tekstury, TextFormat("stage/%i.txt", *num), radius, player);
        map[*num] = (struct map){
            .grid = grid,
            .camera = createCamera(width, height, radius),
            .height = height,
            .width = width
        };
    }

    // player.coordinates = grid[interY][interX].expectedCoordinates;

}

void paint(struct GridTile **grid, int width, int height) {
    int i = 0;
    int j = 0;

    while (i < height) {
        j = 0;
        while (j < width) {
            DrawTextureEx(*grid[i][j].texture, grid[i][j].coordinates, 0, 1, WHITE);
            if (grid[i][j].object != NULL) DrawTextureEx(*grid[i][j].object, grid[i][j].coordinates, 0, 1, WHITE);
            if (grid[i][j].interactable != NULL) DrawTextureEx(*grid[i][j].interactable, grid[i][j].coordinates, 0, 1, WHITE);
            if (grid[i][j].collectable != NULL) DrawTextureEx(*grid[i][j].collectable, grid[i][j].coordinates, 0, 1, WHITE);
            j += 1;
        }

        i += 1;
    }
}

void freeGrid(struct GridTile **toFree, int height) {
    int i = 0;

    if (toFree != NULL) {
        while (i < height) {
            free(toFree[i]);
            i += 1;
        }

        free(toFree);
    }
}