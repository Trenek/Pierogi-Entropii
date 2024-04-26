#include <stdio.h>

#include <raylib.h>

#include "state.h"

#include "drawMenuElement.h"

void play(enum state *state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    while (!WindowShouldClose() && *state == PLAY) {
        BeginDrawing();
        ClearBackground(color);

        drawMenuElement("Menu", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, &color2, &color3);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickAndChangeState(state, "Menu", 20, GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, MENU);
        }
    }
}