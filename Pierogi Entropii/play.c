#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>

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

const char * const znaleziska[] = {
    "ZNALAZLES PIEROGA!!!",
    "ZNALAZLES BANANA Z WORMSOW!!!",
    "ZNALAZLES JAJO Z WASEM!!!",
    "ZNALAZLES BOZA KIELBASE MAJORA!!!",
    "ZNALAZLES PLYTE Z PYTHONEM!!!",
    "ZNALAZLES RYBE KTORA SMIERDZI (WCALE NIE!)!!!",
    "ZNALAZLES PAPIER TOALETOWY!!!",
    "ZNALAZLES DZIEKANA BIOLOGII!!!",
    "ZNALAZLES DZIEKANA WCHUJ!!!",
    "ZNALAZLES DZIEKANA FAISUJ!!!",
    "ZNALAZLES WIELKI MIECZ Z RPG!!!",
    "ZNALAZLES DZIEKANA ZiKSUJ!!!",
    "ZNALAZLES DZIEKANA LEKARSKIEGO!!!",
    "ZNALAZLES DZIEKANA WMiIUJ!!!",
    "ZNALAZLES DZIEKANA POLONISTYKI!!!",
    "ZNALAZLES UNITY"
};

void play(enum state *state) {
    extern time_t lifetime;
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    int width = 8;
    int height = 10;
    int radius = 16;
    time_t start = time(NULL);

    Texture *tekstury[] = {
        LoadFloor(),
        LoadProps(),
        LoadClickable(),
        LoadCollectable()
    };
    struct player player = { .orientation = 0, .texture = LoadPlayer(), .pierogi = { 0 } };

    InitAudioDevice();              // Initialize audio device
    Music music = LoadMusicStream("resources/mp3/muzyka.mp3");
    PlayMusicStream(music);

    struct map *realMap = malloc(sizeof(struct map) * 100);
    struct map *map = realMap + 1;

    for (int i = 0; i < 100; i += 1) {
        realMap[i].height = 0;
        realMap[i].grid = NULL;
        realMap[i].width = 0;
    }

    struct GridTile **grid = allocGridTile(&width, &height, tekstury, "stage/1.txt", radius, &player);
    int num = 1;
    map[num] = (struct map){
        .grid = grid,
        .camera = createCamera(width, height, radius),
        .height = height,
        .width = width
    };
    int is[100] = { 0 };
    is[1] = 1;
    RenderTexture screenCamera1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float)-screenCamera1.texture.height };
    int interX = 0;
    int interY = 0;
    bool interact = false;
    bool isCentered = false;
    bool won = false;

    while (!WindowShouldClose() && *state == PLAY && !won) {
        if (lifetime - time(NULL) + start <= 0) {
            *state = MENU;
        }
        UpdateMusicStream(music);
        if (isCentered) {
            map[num].camera.target = Vector2Scale(player.coordinates, radius);
            if (map[num].camera.zoom <= 5) map[num].camera.zoom = 5;
        }
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
            DrawRectangle((GetScreenWidth() - 20 - MeasureText(TextFormat("%3is", lifetime - (time(NULL) - start)), 30)) / 2, 0, MeasureText(TextFormat("%3is", lifetime - (time(NULL) - start)), 30) + 40, 40, VIOLET);
            DrawText(TextFormat("%3is", lifetime - (time(NULL) - start)), (GetScreenWidth() - MeasureText(TextFormat("%3is", lifetime - (time(NULL) - start)), 30)) / 2, 0, 30, WHITE);
            if (interact) {
                //DrawText(TextFormat("%i", map[num].grid[interY][interX].interactableID), 0, 0, 20, WHITE);
                switch (map[num].grid[interY][interX].interactableID) {
                    case 1:
                        DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 300, 50, GREEN);
                        DrawText("Przeszukaj skrzynke", (GetScreenWidth() - MeasureText("Przeszukaj skrzynke", 20)) / 2, GetScreenHeight() - 30, 20, WHITE);
                        if (IsKeyPressed(KEY_X)) {
                            if (map[num].grid[interY][interX].exit > 0) {
                                player.pierogi[map[num].grid[interY][interX].exit - 1] += 1;
                                int s = map[num].grid[interY][interX].exit - 1;
                                map[num].grid[interY][interX].exit = 0;
                                do {
                                    UpdateMusicStream(music);
                                    BeginDrawing();
                                    ClearBackground(GREEN);


                                    DrawText(znaleziska[s], (GetScreenWidth() - MeasureText(znaleziska[s], 30)) / 2, (GetScreenHeight() - 30) / 2, 30, WHITE);
                                    EndDrawing();
                                } while (GetKeyPressed() == 0);
                            }
                            else {
                                do {
                                    UpdateMusicStream(music);
                                    BeginDrawing();
                                    ClearBackground(RED);
                                    DrawText("Z pustego i Salomon nie naleje", (GetScreenWidth() - MeasureText("Z pustego i Salomon nie naleje", 30)) / 2, (GetScreenHeight() - 30) / 2, 30, WHITE);
                                    EndDrawing();
                                } while (GetKeyPressed() == 0);
                            }
                        }
                        break;
                    case 2:
                        DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 300, 50, GREEN);
                        DrawText(TextFormat("Go to stage %i", map[num].grid[interY][interX].exit), (GetScreenWidth() - MeasureText(TextFormat("Go to stage %i", map[num].grid[interY][interX].exit), 20)) / 2, GetScreenHeight() - 30, 20, WHITE);

                        if (IsKeyPressed(KEY_X)) {
                            map[num].position = player.coordinates;
                            map[num].camera = createCamera(map[num].width, map[num].height, radius);
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
                            player.coordinates = grid[interY][interX].expectedCoordinates;
                            interact = false;
                        }
                        break;
                    case 4:
                        DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 300, 50, GREEN);
                        DrawText("Zakoncz Rozgrywke", (GetScreenWidth() - MeasureText("Zakoncz Rozgrywke", 20)) / 2, GetScreenHeight() - 30, 20, WHITE);

                        if (IsKeyPressed(KEY_X)) {
                            won = true;
                        }
                    default:
                        DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 300, 50, GREEN);
                        DrawText("Click x to exit", (GetScreenWidth() - MeasureText("Click x to exit", 20)) / 2, GetScreenHeight() - 30, 20, WHITE);

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


        float speed = 0.01f;
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            speed *= 4;
        }
        if (IsKeyPressed(KEY_Q)) {
            isCentered = !isCentered;
            if (!isCentered) {
                map[num].camera = createCamera(map[num].width, map[num].height, radius);
            }
        }
        if (IsKeyDown(KEY_W)) {
            int x1 = (int)floorf(player.coordinates.x + 0.20);
            int x2 = (int)floorf(player.coordinates.x + 0.8f);
            int y = (int)floorf(player.coordinates.y - speed + 1.f);

            if (map[num].grid[y][x1].object == NULL && map[num].grid[y][x2].object == NULL) {
                player.orientation = 2;
                player.coordinates.y -= speed;
                if (map[num].grid[y][x1].collectable != NULL) {
                    map[num].grid[y][x1].collectable = NULL;
                    player.pierogi[map[num].grid[y][x1].exit] += 1;
                }
                if (map[num].grid[y][x2].collectable != NULL) {
                    map[num].grid[y][x2].collectable = NULL;
                    player.pierogi[map[num].grid[y][x1].exit] += 1;
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
            int y = (int)floorf(player.coordinates.y + speed + 1.f);

            if (map[num].grid[y][x1].object == NULL && map[num].grid[y][x2].object == NULL) {
                player.orientation = 0;
                player.coordinates.y += speed;
                if (map[num].grid[y][x1].collectable != NULL) {
                    map[num].grid[y][x1].collectable = NULL;
                    player.pierogi[map[num].grid[y][x1].exit] += 1;
                }

                if (map[num].grid[y][x2].collectable != NULL) {
                    map[num].grid[y][x2].collectable = NULL;
                    player.pierogi[map[num].grid[y][x1].exit] += 1;
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
            int x1 = (int)floorf(player.coordinates.x + speed + 0.2f);
            int x2 = (int)floorf(player.coordinates.x + speed + 0.8f);
            int y = (int)floorf(player.coordinates.y + 1.f);

            if (map[num].grid[y][x1].object == NULL && map[num].grid[y][x2].object == NULL) {
                player.orientation = 1;
                player.coordinates.x += speed;
                if (map[num].grid[y][x1].collectable != NULL) {
                    map[num].grid[y][x1].collectable = NULL;
                    player.pierogi[map[num].grid[y][x1].exit] += 1;
                }

                if (map[num].grid[y][x2].collectable != NULL) {
                    map[num].grid[y][x2].collectable = NULL;
                    player.pierogi[map[num].grid[y][x1].exit] += 1;
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
            int x1 = (int)floorf(player.coordinates.x - speed + 0.2f);
            int x2 = (int)floorf(player.coordinates.x - speed + 0.8f);
            int y = (int)floorf(player.coordinates.y + 1.f);

            if (map[num].grid[y][x1].object == NULL && map[num].grid[y][x2].object == NULL) {
                player.orientation = 3;
                player.coordinates.x -= speed;
                if (map[num].grid[y][x1].collectable != NULL) {
                    map[num].grid[y][x1].collectable = NULL;
                    player.pierogi[map[num].grid[y][x1].exit] += 1;
                }

                if (map[num].grid[y][x2].collectable != NULL) {
                    map[num].grid[y][x2].collectable = NULL;
                    player.pierogi[map[num].grid[y][x1].exit] += 1;
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

    if (won) {
        endScreen(state, MENU, &screenCamera1, &splitScreenRect, player);
    }
    else {
        do {
            UpdateMusicStream(music);
            BeginDrawing();
            ClearBackground(RED);
            DrawText("Przegrales", (GetScreenWidth() - MeasureText("Przegrales", 30)) / 2, (GetScreenHeight() - 30) / 2 + 50, 30, WHITE);
            DrawText("Nie zdolales dotrzec do czajnika", (GetScreenWidth() - MeasureText("Nie zdolales dotrzec do czajnika", 30)) / 2, (GetScreenHeight() - 30) / 2, 30, WHITE);
            EndDrawing();
        } while (GetKeyPressed() == 0);
    }

    UnloadMusicStream(music);

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    UnloadFloor(tekstury[0]);
    UnloadProps(tekstury[1]);
    UnloadClickable(tekstury[2]);
    UnloadCollectable(tekstury[3]);
    UnloadPlayer(player.texture);
    
    int i = 0;
    while (i < 100) {
        if (realMap[i].height != 0)
        freeGrid(realMap[i].grid, realMap[i].height);

        i += 1;
    }
}