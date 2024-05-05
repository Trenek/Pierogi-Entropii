#include <raylib.h>
#include <math.h>

#include "player.h"
#include "map.h"

bool static check(struct player *player, struct map map, int x1, int x2, int y, int *interX, int *interY) {
    bool interact = false;

    if (map.grid[y][x1].collectable != NULL) {
        map.grid[y][x1].collectable = NULL;
        player->collectables[map.grid[y][x1].exit] += 1;
    }
    if (map.grid[y][x2].collectable != NULL) {
        map.grid[y][x2].collectable = NULL;
        player->collectables[map.grid[y][x2].exit] += 1;
    }

    if (map.grid[y][x1].interactable != NULL) {
        *interX = x1;
        *interY = y;
        interact = true;
    }
    else if (map.grid[y][x2].interactable != NULL) {
        *interX = x2;
        *interY = y;
        interact = true;
    }

    return interact;
}

void movePlayer(struct player *player, struct map map, bool *interact, int *interX, int *interY) {
    float speed = 2.4f * GetFrameTime();
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        speed *= 4;
    }

    int x1 = 0;
    int x2 = 0;
    int y = 0;

    if (IsKeyDown(KEY_W)) {
        x1 = (int)floorf(player->coordinates.x + 0.2f);
        x2 = (int)floorf(player->coordinates.x + 0.8f);
        y = (int)floorf(player->coordinates.y - speed + 1.f);

        if (map.grid[y][x1].object == NULL && map.grid[y][x2].object == NULL) {
            player->orientation = 2;
            player->coordinates.y -= speed;
            *interact = check(player, map, x1, x2, y, interX, interY);
        }
    }
    else if (IsKeyDown(KEY_S)) {
        x1 = (int)floorf(player->coordinates.x + 0.2f);
        x2 = (int)floorf(player->coordinates.x + 0.8f);
        y = (int)floorf(player->coordinates.y + speed + 1.f);

        if (map.grid[y][x1].object == NULL && map.grid[y][x2].object == NULL) {
            player->orientation = 0;
            player->coordinates.y += speed;
            *interact = check(player, map, x1, x2, y, interX, interY);
        }
    }
    else if (IsKeyDown(KEY_D)) {
        x1 = (int)floorf(player->coordinates.x + speed + 0.2f);
        x2 = (int)floorf(player->coordinates.x + speed + 0.8f);
        y = (int)floorf(player->coordinates.y + 1.f);

        if (map.grid[y][x1].object == NULL && map.grid[y][x2].object == NULL) {
            player->orientation = 1;
            player->coordinates.x += speed;
            *interact = check(player, map, x1, x2, y, interX, interY);
        }
    }
    else if (IsKeyDown(KEY_A)) {
        x1 = (int)floorf(player->coordinates.x - speed + 0.2f);
        x2 = (int)floorf(player->coordinates.x - speed + 0.8f);
        y = (int)floorf(player->coordinates.y + 1.f);

        if (map.grid[y][x1].object == NULL && map.grid[y][x2].object == NULL) {
            player->orientation = 3;
            player->coordinates.x -= speed;
            *interact = check(player, map, x1, x2, y, interX, interY);
        }
    }

    if (player->coordinates.x + 0.2f < 1) player->coordinates.x = 0.8f;
    if (player->coordinates.x + 0.81f > map.width - 1) player->coordinates.x = map.width - 1 - 0.81f;
    if (player->coordinates.y + 1.f < 1) player->coordinates.y = 0;
    if (player->coordinates.y > map.height - 2.01f) player->coordinates.y = map.height - 2.01f;
}