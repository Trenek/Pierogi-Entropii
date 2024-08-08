#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "player.h"

#include "drawMenuElement.h"

#include "collectablesStrings.h"

void equipment(enum state *state, enum state resumeState, RenderTexture *screenCamera1, Rectangle *splitScreenRect, struct player player) {
    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };
    int i = 0;

    *state = EQUIPMENT;
    do {
        BeginDrawing();

        ClearBackground(color1);
        if (screenCamera1 != NULL) DrawTextureRec(screenCamera1->texture, *splitScreenRect, (Vector2) { 0, 0 }, WHITE);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);

        DrawRectangle(GetScreenWidth() / 4, 0, GetScreenWidth() / 2, 18 * GetScreenHeight() >> 5, (Color){.r = 150, .g = 150, .b = 30, .a = 200 });

        i = 0;
        while (i < 16) {
            drawMenuElement(TextFormat(liczba[i], player.collectables[i]), 20, GetScreenWidth() >> 1, (i + 1) * GetScreenHeight() >> 5, 10, 10, NULL, NULL);

            i += 1;
        }

        EndDrawing();

        if (IsKeyPressed(KEY_E)) {
            *state = resumeState;
        }
    } while (*state == EQUIPMENT && !WindowShouldClose());
}