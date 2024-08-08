#include <stdlib.h>

#include "map.h"
#include "gridTile.h"

struct map *allocMapArray(int num) {
    struct map *result = malloc(sizeof(struct map) * num);
    int i = 0;

    while (i < num) {
        result[i].height = 0;
        result[i].grid = NULL;
        result[i].width = 0;

        i += 1;
    }

    return result;
}

void freeMapArray(struct map map[], int num) {
    int i = 0;

    while (i < num) {
        if (map[i].height != 0)
        freeGrid(map[i].grid, map[i].height);

        i += 1;
    }

    free(map);
}