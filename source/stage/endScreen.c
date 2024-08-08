#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "player.h"

#include "drawMenuElement.h"

#include "collectablesStrings.h"

void endScreen(enum state *state, enum state resumeState, RenderTexture *screenCamera1, Rectangle *splitScreenRect, struct player player) {
    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };
    int a[] = { 5, 20, 50, 15, 10, -1, 2, 1000, 1000, 1000, 100, 1000, 1000, 1000, 1000, 1 };
    int sum = 0;
    int i = 0;

    while (i < 16) {
        sum += a[i] * player.collectables[i];

        i += 1;
    }

    *state = EQUIPMENT;
    do {
        BeginDrawing();

        ClearBackground(color1);
        if (screenCamera1 != NULL) DrawTextureRec(screenCamera1->texture, *splitScreenRect, (Vector2) { 0, 0 }, WHITE);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);

        DrawRectangle(GetScreenWidth() / 4, 0, GetScreenWidth() / 2, 18 * GetScreenHeight() >> 5, (Color) { .r = 150, .g = 150, .b = 30, .a = 200 });
        i = 0;
        while (i < 16) {
            drawMenuElement(TextFormat(liczba[i], player.collectables[i]), 20, GetScreenWidth() >> 1, (i + 1) * GetScreenHeight() >> 5, 10, 10, NULL, NULL);

            i += 1;
        }

        drawMenuElement(TextFormat("Wynik: %i", sum), 30, GetScreenWidth() >> 1, 3 * (GetScreenHeight() >> 2) - 80, 10, 10, &VIOLET, &VIOLET);
        DrawText("Kliknij klawisz spacji aby kontytuowac", (GetScreenWidth() >> 1) - (MeasureText("Kliknij klawisz spacji aby kontytuowac", 30) / 2), 3 * (GetScreenHeight() >> 2), 30, (Color) { .r = 47, .g = 78, .b = 37, .a = 255 });

        EndDrawing();

        if (IsKeyPressed(KEY_SPACE)) {
            *state = resumeState;
        }
    } while (*state == EQUIPMENT && !WindowShouldClose());
}