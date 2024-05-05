#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>

#include "state.h"
#include "gridTile.h"
#include "map.h"

#include "drawMenuElement.h"
#include "player.h"
#include "createCamera.h"

#include "textures.h"

#include "collectablesStrings.h"
#include "cancelKey.h"

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
    struct player player = { .orientation = 0, .texture = LoadPlayer(), .collectables = { 0 } };

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

    int num = 1;
    struct GridTile **grid = allocGridTile(&width, &height, tekstury, TextFormat("stage/%i.txt", num), radius, &player);
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

    bool getItem = false;

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
                            getItem = true;
                        }
                        break;
                    case 2:
                        DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 300, 50, GREEN);
                        DrawText(TextFormat("Go to stage %i", map[num].grid[interY][interX].exit), (GetScreenWidth() - MeasureText(TextFormat("Go to stage %i", map[num].grid[interY][interX].exit), 20)) / 2, GetScreenHeight() - 30, 20, WHITE);

                        if (IsKeyPressed(KEY_X)) {
                            changeStage(map, &player, interY, interX, tekstury, is, &num);
                            cancelKey(KEY_X);
                            interY = (int)player.coordinates.y;
                            interX = (int)player.coordinates.x;
                        }
                        break;
                    case 4:
                        DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 300, 50, GREEN);
                        DrawText("Zakoncz Rozgrywke", (GetScreenWidth() - MeasureText("Zakoncz Rozgrywke", 20)) / 2, GetScreenHeight() - 30, 20, WHITE);

                        if (IsKeyPressed(KEY_X)) {
                            won = true;
                        }
                }
            }
        EndDrawing();

        if (getItem) {
            if (map[num].grid[interY][interX].exit > 0) {
                player.collectables[map[num].grid[interY][interX].exit - 1] += 1;
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
            getItem = false;
            cancelKey(KEY_X);
        }

        if (IsKeyPressed(KEY_P)) {
            time_t begin = time(NULL);
            Pause(state, PLAY, &screenCamera1, &splitScreenRect);
            start += time(NULL) - begin;
        }
        if (IsKeyPressed(KEY_E)) {
            equipment(state, PLAY, &screenCamera1, &splitScreenRect, player);
        }

        if (IsKeyPressed(KEY_Q)) {
            isCentered = !isCentered;
            if (!isCentered) {
                map[num].camera = createCamera(map[num].width, map[num].height, radius);
            }
        }
        movePlayer(&player, map[num], &interact, &interX, &interY);
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