#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <raylib.h>

#include "state.h"
#include "gridTile.h"

#include "drawMenuElement.h"
#include "player.h"

#include "textures.h"

void paint(struct GridTile **grid, int width, int height) {
    int i = 0;
    int j = 0;

    while (i < height) {
        j = 0;
        while (j < width) {
            DrawRectangle((int)grid[i][j].coordinates.x, (int)grid[i][j].coordinates.y, 8, 8, grid[i][j].color);
            DrawTextureEx(*grid[i][j].texture, grid[i][j].coordinates, 0, 1, WHITE);
            if (grid[i][j].object != NULL) DrawTextureEx(*grid[i][j].object, grid[i][j].coordinates, 0, 1, WHITE);
            if (grid[i][j].interactable != NULL) DrawTextureEx(*grid[i][j].interactable, grid[i][j].coordinates, 0, 1, WHITE);
            if (grid[i][j].collectable != NULL) DrawTextureEx(*grid[i][j].collectable, grid[i][j].coordinates, 0, 1, WHITE);
            j += 1;
        }

        i += 1;
    }
}

inline Camera2D createCamera(int width, int height, int radius) {
    float zoom = width > height ?
        GetScreenWidth() / (radius * (width)) :
        GetScreenHeight() / (radius * (height));
    
    return (Camera2D) {
        .target = (Vector2){ radius * width / 2, radius * height / 2 },
        .offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f },
        .rotation = 0.0f,
        .zoom = zoom
    };
}


struct map {
    struct GridTile **grid;
    Camera2D camera;
    int height;
    int width;
    Vector2 position;
};


void play(enum state *state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    int width = 8;
    int height = 10;
    int radius = 16;

    Texture *tekstury[] = {
        LoadFloor(),
        LoadProps(),
        LoadClickable(),
        LoadCollectable()
    };
    struct player player = { .orientation = 0, .texture = LoadPlayer(), .pierogi = { 0 } };


    struct map *realMap = malloc(sizeof(struct map) * 10);
    struct map *map = realMap + 1;

    struct GridTile **grid = allocGridTile(&width, &height, tekstury, "stage/1.txt", radius, &player);
    int num = 1;
    map[num] = (struct map){
        .grid = grid,
        .camera = createCamera(width, height, radius),
        .height = height,
        .width = width
    };
    int is[10] = { 0 };
    is[1] = 1;
    RenderTexture screenCamera1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float)-screenCamera1.texture.height };
    int interX = 0;
    int interY = 0;
    bool interact = false;

    while (!WindowShouldClose() && *state == PLAY) {
        BeginTextureMode(screenCamera1);
            ClearBackground(BROWN);

            BeginMode2D(map[num].camera);
                paint(map[num].grid, map[num].width, map[num].height);
                DrawTextureEx(player.texture[player.orientation], (Vector2) { player.coordinates.x * radius, player.coordinates.y * radius }, 0, 1, WHITE);
            EndMode2D();

        EndTextureMode();

        BeginDrawing();
            ClearBackground(color);
            DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);
            DrawText(TextFormat("LICZBA PIEROGOW - %i", player.pierogi[0]), 0, 0, 20, WHITE);
            if (interact) {
                //DrawText(TextFormat("%i", map[num].grid[interY][interX].interactableID), 0, 0, 20, WHITE);
                switch (map[num].grid[interY][interX].interactableID) {
                    case 1:
                        DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() - 100, 200, 50, GREEN);
                        DrawText("Przeszukaj skrzynke", GetScreenWidth() / 2 - 80, GetScreenHeight() - 80, 20, WHITE);
                        if (IsKeyPressed(KEY_X)) {
                            if (map[num].grid[interY][interX].exit > 0) {
                                player.pierogi[0] += map[num].grid[interY][interX].exit;
                                map[num].grid[interY][interX].exit = 0;
                                do {
                                    BeginDrawing();
                                    ClearBackground(GREEN);
                                    DrawText("ZNALAZLES PIEROGA!!!", (GetScreenWidth() - MeasureText("ZNALAZLES PIEROGA!!!", 50)) / 2, (GetScreenHeight() - 50) / 2, 50, WHITE);
                                    EndDrawing();
                                } while (GetKeyPressed() == 0);
                            }
                            else {
                                do {
                                    BeginDrawing();
                                    ClearBackground(RED);
                                    DrawText("NIE DLA PSA!!!", (GetScreenWidth() - MeasureText("NIE DLA PSA!!!", 50)) / 2, (GetScreenHeight() - 50) / 2, 50, WHITE);
                                    EndDrawing();
                                } while (GetKeyPressed() == 0);
                            }
                        }
                        break;
                    case 2:
                        DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() - 100, 200, 50, GREEN);
                        DrawText("Go to other stage", GetScreenWidth() / 2 - 80, GetScreenHeight() - 80, 20, WHITE);
                        if (IsKeyPressed(KEY_X)) {
                            map[num].position = player.coordinates;
                            num = map[num].grid[interY][interX].exit;
                            if (is[num] == 0) {
                                is[num] = 1;
                                grid = allocGridTile(&width, &height, tekstury, TextFormat("stage/%i.txt", num), radius, &player);
                                map[num] = (struct map) {
                                    .grid = grid,
                                    .camera = createCamera(width, height, radius),
                                    .height = height,
                                    .width = width
                                };
                            }
                            else {
                                player.coordinates = map[num].position;
                            }
                            interact = false;
                        }
                        break;
                    default:
                        DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() - 100, 200, 50, GREEN);
                        DrawText("Click x to exit", GetScreenWidth() / 2 - 80, GetScreenHeight() - 80, 20, WHITE);
                        if (IsKeyDown(KEY_X)) {
                            *state = EXIT;
                        }
                }
            }
            EndDrawing();

        if (IsKeyPressed(KEY_P)) {
            Pause(state, PLAY, &screenCamera1, &splitScreenRect);
        }
        if (IsKeyPressed(KEY_E)) {
            equipment(state, PLAY, &screenCamera1, &splitScreenRect, player);
        }

        if (IsKeyDown(KEY_W)) {
            int x1 = (int)floorf(player.coordinates.x + 0.20);
            int x2 = (int)floorf(player.coordinates.x + 0.8f);
            int y = (int)floorf(player.coordinates.y - 0.01f + 1.f);

            if (map[num].grid[y][x1].object == NULL && map[num].grid[y][x2].object == NULL) {
                player.orientation = 2;
                player.coordinates.y -= 0.01f;
                if (map[num].grid[y][x1].collectable != NULL) {
                    map[num].grid[y][x1].collectable = NULL;
                    player.pierogi[0] += 1;
                }
                if (map[num].grid[y][x2].collectable != NULL) {
                    map[num].grid[y][x2].collectable = NULL;
                    player.pierogi[0] += 1;
                }

                if (map[num].grid[y][x1].interactable != NULL) {
                    interX = x1;
                    interY = y;
                    interact = true;
                }
                else if (map[num].grid[y][x2].interactable != NULL) {
                    interX = x2;
                    interY = y;
                    interact = true;
                }
                else interact = false;
            }
        }
        else if (IsKeyDown(KEY_S)) {
            int x1 = (int)floorf(player.coordinates.x + 0.2f);
            int x2 = (int)floorf(player.coordinates.x + 0.8f);
            int y = (int)floorf(player.coordinates.y + 0.01f + 1.f);

            if (map[num].grid[y][x1].object == NULL && map[num].grid[y][x2].object == NULL) {
                player.orientation = 0;
                player.coordinates.y += 0.01f;
                if (map[num].grid[y][x1].collectable != NULL) {
                    map[num].grid[y][x1].collectable = NULL;
                    player.pierogi[0] += 1;
                }

                if (map[num].grid[y][x2].collectable != NULL) {
                    map[num].grid[y][x2].collectable = NULL;
                    player.pierogi[0] += 1;
                }

                if (map[num].grid[y][x1].interactable != NULL) {
                    interX = x1;
                    interY = y;
                    interact = true;
                }
                else if (map[num].grid[y][x2].interactable != NULL) {
                    interX = x2;
                    interY = y;
                    interact = true;
                }
                else interact = false;
            }
        }
        else if (IsKeyDown(KEY_D)) {
            int x1 = (int)floorf(player.coordinates.x + 0.01f + 0.2f);
            int x2 = (int)floorf(player.coordinates.x + 0.01f + 0.8f);
            int y = (int)floorf(player.coordinates.y + 1.f);

            if (map[num].grid[y][x1].object == NULL && map[num].grid[y][x2].object == NULL) {
                player.orientation = 1;
                player.coordinates.x += 0.01f;
                if (map[num].grid[y][x1].collectable != NULL) {
                    map[num].grid[y][x1].collectable = NULL;
                    player.pierogi[0] += 1;
                }

                if (map[num].grid[y][x2].collectable != NULL) {
                    map[num].grid[y][x2].collectable = NULL;
                    player.pierogi[0] += 1;
                }

                if (map[num].grid[y][x1].interactable != NULL) {
                    interX = x1;
                    interY = y;
                    interact = true;
                }
                else if (map[num].grid[y][x2].interactable != NULL) {
                    interX = x2;
                    interY = y;
                    interact = true;
                }
                else interact = false;
            }
        }
        else if (IsKeyDown(KEY_A)) {
            int x1 = (int)floorf(player.coordinates.x - 0.01f + 0.2f);
            int x2 = (int)floorf(player.coordinates.x - 0.01f + 0.8f);
            int y = (int)floorf(player.coordinates.y + 1.f);

            if (map[num].grid[y][x1].object == NULL && map[num].grid[y][x2].object == NULL) {
                player.orientation = 3;
                player.coordinates.x -= 0.01f;
                if (map[num].grid[y][x1].collectable != NULL) {
                    map[num].grid[y][x1].collectable = NULL;
                    player.pierogi[0] += 1;
                }

                if (map[num].grid[y][x2].collectable != NULL) {
                    map[num].grid[y][x2].collectable = NULL;
                    player.pierogi[0] += 1;
                }

                if (map[num].grid[y][x1].interactable != NULL) {
                    interX = x1;
                    interY = y;
                    interact = true;
                }
                else if (map[num].grid[y][x2].interactable != NULL) {
                    interX = x2;
                    interY = y;
                    interact = true;
                }
                else interact = false;
            }
        }

        if (player.coordinates.x + 0.2f < 1) player.coordinates.x = 0.8f;
        if (player.coordinates.x + 0.8f > map[num].width - 1) player.coordinates.x = map[num].width - 1 - 0.8f;
        if (player.coordinates.y + 1.f < 1) player.coordinates.y = 0;
        if (player.coordinates.y > map[num].height - 2) player.coordinates.y = map[num].height - 2;

        map[num].camera.zoom += (GetMouseWheelMove() * map[num].camera.zoom / 16);
    }
}