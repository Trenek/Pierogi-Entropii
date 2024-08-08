#include <stdio.h>

#include <raylib.h>

#include "state.h"

#include "drawMenuElement.h"

void timeMenu(enum state *state) {
    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };
    extern time_t lifetime;

    while (!WindowShouldClose() && *state == TIME) {
        BeginDrawing();
        ClearBackground(color);

        drawTitle("Wybierz limit czasowy", 60, GetScreenWidth() >> 1, GetScreenHeight() >> 4, 10, 10, NULL, NULL);
        drawMenuElement("1 Minuta", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1), 10, 10, &color2, &color3);
        drawMenuElement("2 Minuty", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 50, 10, 10, &color2, &color3);
        drawMenuElement("5 Minut", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 100, 10, 10, &color2, &color3);

        drawMenuElement("Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, &color2, &color3);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseInRange(GetScreenWidth() >> 1, GetScreenHeight() >> 1, 10, 10, 20, "1 Minuta")) {
                lifetime = 60;
                *state = PLAY;
            }
            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 50, 10, 10, 20, "2 Minuty")) {
                lifetime = 2 * 60;
                *state = PLAY;
            }
            if (isMouseInRange(GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 100, 10, 10, 20, "5 Minut")) {
                lifetime = 5 * 60;
                *state = PLAY;
            }

            clickAndChangeState(state, "Back", 20, GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 200, 10, 10, MENU);
        }
    }
}