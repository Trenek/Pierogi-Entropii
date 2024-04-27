#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <raylib.h>

#include "state.h"

#include "drawMenuElement.h"

struct GridTile {
    Vector2 coordinates;
    Color color;
    Texture2D *texture;
    Texture2D *object;
};

struct GridTile **allocGridTile(int *width, int *height, Texture2D *texture, const char *file, int radius) {
    FILE *f = fopen(file, "r");
    fscanf(f, "%i%i", height, width);
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
                .texture = texture + k
            };

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

void paint(struct GridTile **grid, int width, int height) {
    int i = 0;
    int j = 0;

    while (i < height) {
        j = 0;
        while (j < width) {
            DrawRectangle((int)grid[i][j].coordinates.x, (int)grid[i][j].coordinates.y, 8, 8, grid[i][j].color);
            DrawTextureEx(*grid[i][j].texture, grid[i][j].coordinates, 0, 1, WHITE);
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

Texture2D *LoadFloor(void) {
    Texture2D *result = malloc(sizeof(Texture2D) * 13);

    result[0] = LoadTexture("resources/Fundamenty/floor.png");
    result[1] = LoadTexture("resources/Fundamenty/upperWall.png");
    result[2] = LoadTexture("resources/Fundamenty/lowerWall.png");
    result[3] = LoadTexture("resources/Fundamenty/leftWall.png");
    result[4] = LoadTexture("resources/Fundamenty/rightWall.png");
    result[5] = LoadTexture("resources/Fundamenty/leftUpperWall.png");
    result[6] = LoadTexture("resources/Fundamenty/rightUpperWall.png");
    result[7] = LoadTexture("resources/Fundamenty/leftLowerWall.png");
    result[8] = LoadTexture("resources/Fundamenty/rightLowerWall.png");
    result[9] = LoadTexture("resources/Fundamenty/DrzwiPrawe.png");
    result[10] = LoadTexture("resources/Fundamenty/DrzwiDolne.png");
    result[11] = LoadTexture("resources/Fundamenty/DrzwiLewe.png");
    result[12] = LoadTexture("resources/Fundamenty/DrzwiGora.png");

    return result;
}

void play(enum state *state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    int width = 8;
    int height = 10;
    int radius = 16;

    Texture2D* podloga = LoadFloor();
    struct GridTile **grid = allocGridTile(&width, &height, podloga, "stage/1.txt", radius);
    Camera2D camera = createCamera(width, height, radius);
    RenderTexture screenCamera1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float)-screenCamera1.texture.height };

    while (!WindowShouldClose() && *state == PLAY) {
        BeginTextureMode(screenCamera1);
            ClearBackground(BROWN);

            BeginMode2D(camera);
                paint(grid, width, height);
            EndMode2D();

        EndTextureMode();

        BeginDrawing();
            ClearBackground(color);
            DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2) { 0, 0 }, WHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_P)) {
            Pause(state, PLAY, &screenCamera1, &splitScreenRect);
        }
        camera.zoom += (GetMouseWheelMove() * camera.zoom / 16);
    }

    freeGrid(grid, height);
}