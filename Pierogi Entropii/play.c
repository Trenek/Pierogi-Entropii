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
    *width = 30;
    *height = 30;
    srand((unsigned int)time(NULL));

    struct GridTile **result = malloc(sizeof(struct GridTile *) * *height);
    int i = 0;
    int j = 0;

    while (i < *height) {
        result[i] = malloc(sizeof(struct GridTile) * *width);
        j = 0;
        while (j < *width) {
            result[i][j] = (struct GridTile){
                //.color = RED,
                .color = { (unsigned char)rand(), (unsigned char)rand(), (unsigned char)rand(), 255 },
                .coordinates = {.x = i * radius, .y = j * radius },
                .object = NULL,
                .texture = texture
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

Texture2D *LoadTextures() {
    Texture2D *result = malloc(sizeof(Texture2D) * 9) = {
        
    }
}

void play(enum state *state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    int width = 8;
    int height = 10;
    int radius = 16;

    Image image = LoadImage("resources/Fais/floor.png");
    Texture2D* podloga = LoadTextures();
    UnloadImage(image);
    struct GridTile **grid = allocGridTile(&width, &height, &podloga, NULL, radius);
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
            drawMenuElement("Menu", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, &color2, &color3);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Menu", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, MENU);
        }
        camera.zoom += (GetMouseWheelMove() * camera.zoom / 16);
    }

    freeGrid(grid, height);
}