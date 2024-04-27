#include <stdio.h>

#include <raylib.h>

#include "state.h"
#include "player.h"

#include "drawMenuElement.h"

void equipment(enum state *state, enum state resumeState, RenderTexture *screenCamera1, Rectangle *splitScreenRect, struct player player) {
    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };

    *state = EQUIPMENT;
    do {
        BeginDrawing();

        ClearBackground(color1);
        if (screenCamera1 != NULL) DrawTextureRec(screenCamera1->texture, *splitScreenRect, (Vector2) { 0, 0 }, WHITE);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);
        //ClearBackground(color1);

        DrawRectangle(GetScreenWidth() / 4, 0, GetScreenWidth() / 2, 18 * GetScreenHeight() >> 5, (Color){.r = 150, .g = 150, .b = 30, .a = 200 });
        drawMenuElement(TextFormat("Liczba Pierogow - %i", player.pierogi[0]), 20, GetScreenWidth() >> 1,                   1 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Liczba Bananow z Wormsow - %i", player.pierogi[1]), 20, GetScreenWidth() >> 1,          2 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Jaj z wasem - %i", player.pierogi[2]), 20, GetScreenWidth() >> 1,                       3 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Boxe kielby majora - %i", player.pierogi[3]), 20, GetScreenWidth() >> 1,                4 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Papaje - %i", player.pierogi[4]), 20, GetScreenWidth() >> 1,                            5 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Plyty z pythonem - %i", player.pierogi[5]), 20, GetScreenWidth() >> 1,                  6 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Ryba ktora smierdzi (wcale nie!) - %i", player.pierogi[6]), 20, GetScreenWidth() >> 1,  7 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Papier Toaletowy - %i", player.pierogi[7]), 20, GetScreenWidth() >> 1,                         8 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan Biologii - %i", player.pierogi[8]), 20, GetScreenWidth() >> 1,                  9 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan WCHUJu - %i", player.pierogi[9]), 20, GetScreenWidth() >> 1,                    10 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan FAISUJ - %i", player.pierogi[10]), 20, GetScreenWidth() >> 1,                   11 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Wielki Miecz z RPG - %i", player.pierogi[11]), 20, GetScreenWidth() >> 1,              12 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan ZiKSUJ - %i", player.pierogi[12]), 20, GetScreenWidth() >> 1,              13 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan Lekarski - %i", player.pierogi[13]), 20, GetScreenWidth() >> 1,                 14 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan Matematyki - %i", player.pierogi[14]), 20, GetScreenWidth() >> 1,               15 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan Polonistyki - %i", player.pierogi[15]), 20, GetScreenWidth() >> 1,              16 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);


        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        }
        if (IsKeyPressed(KEY_E)) {
            *state = resumeState;
        }
    } while (*state == EQUIPMENT && !WindowShouldClose());
}

void endScreen(enum state *state, enum state resumeState, RenderTexture *screenCamera1, Rectangle *splitScreenRect, struct player player) {
    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };
    int a[] = { 5, 20, 50, 15, 10, -1, 2, 1000, 1000, 1000, 100, 1000, 1000, 1000, 1000, 1 };
    int sum = 0;
    int i = 0;

    while (i < 16) {
        sum += a[i] * player.pierogi[i];
        
        i += 1;
    }

    *state = EQUIPMENT;
    do {
        BeginDrawing();

        ClearBackground(color1);
        if (screenCamera1 != NULL) DrawTextureRec(screenCamera1->texture, *splitScreenRect, (Vector2) { 0, 0 }, WHITE);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);
        //ClearBackground(color1);

        DrawRectangle(GetScreenWidth() / 4, 0, GetScreenWidth() / 2, 18 * GetScreenHeight() >> 5, (Color) { .r = 150, .g = 150, .b = 30, .a = 200 });
        drawMenuElement(TextFormat("Liczba Pierogow - %i", player.pierogi[0]), 20, GetScreenWidth() >> 1, 1 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Liczba Bananow z Wormsow - %i", player.pierogi[1]), 20, GetScreenWidth() >> 1, 2 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Jaj z wasem - %i", player.pierogi[2]), 20, GetScreenWidth() >> 1, 3 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Boze kielby majora - %i", player.pierogi[3]), 20, GetScreenWidth() >> 1, 4 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Plyty z pythonem - %i", player.pierogi[4]), 20, GetScreenWidth() >> 1, 5 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Ryba ktora smierdzi (wcale nie!) - %i", player.pierogi[5]), 20, GetScreenWidth() >> 1, 6 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Papier Toaletowy - %i", player.pierogi[6]), 20, GetScreenWidth() >> 1, 7 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan Biologii - %i", player.pierogi[7]), 20, GetScreenWidth() >> 1, 8 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan WCHUJu - %i", player.pierogi[8]), 20, GetScreenWidth() >> 1, 9 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan FAISUJ - %i", player.pierogi[9]), 20, GetScreenWidth() >> 1, 10 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Wielki Miecz z RPG - %i", player.pierogi[10]), 20, GetScreenWidth() >> 1, 11 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan ZiKSUJ - %i", player.pierogi[11]), 20, GetScreenWidth() >> 1, 12 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan Lekarski - %i", player.pierogi[12]), 20, GetScreenWidth() >> 1, 13 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan Matematyki - %i", player.pierogi[13]), 20, GetScreenWidth() >> 1, 14 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Dziekan Polonistyki - %i", player.pierogi[14]), 20, GetScreenWidth() >> 1, 15 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);
        drawMenuElement(TextFormat("Unity - %i", player.pierogi[15]), 20, GetScreenWidth() >> 1, 16 * GetScreenHeight() >> 5, 10, 10, NULL, NULL);

        
        drawMenuElement(TextFormat("Wynik: %i", sum), 30, GetScreenWidth() >> 1, 3 * (GetScreenHeight() >> 2) - 80, 10, 10, &VIOLET, &VIOLET);
        DrawText("Kliknij klawisz spacji aby kontytuowac", (GetScreenWidth() >> 1) - (MeasureText("Kliknij klawisz spacji aby kontytuowac", 30) / 2), 3 * (GetScreenHeight() >> 2), 30, (Color) {.r = 47, .g = 78, .b = 37, .a = 255 });

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        }
        if (IsKeyPressed(KEY_SPACE)) {
            *state = resumeState;
        }
    } while (*state == EQUIPMENT && !WindowShouldClose());
}