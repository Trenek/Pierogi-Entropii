﻿// raylib.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <stdio.h>
#include <raylib.h>

#include "state.h"

//#define FULLSCREEN
time_t lifetime = 0;

int main(void) {
    enum state state = MENU;
    void (*function[])(enum state *state) = {
        [MENU] = menu,
        [TIME] = timeMenu,
        [PLAY] = play
    };

#ifdef FULLSCREEN
    int display = GetCurrentMonitor();
    InitWindow(GetMonitorWidth(display), GetMonitorHeight(display), "Project");
    ToggleFullscreen();
#else
    InitWindow(800, 600, "Project");
#endif

    SetTargetFPS(240);

    while (!WindowShouldClose() && (state != EXIT)) {
        function[state](&state);
    }

    CloseWindow();

    return 0;
}