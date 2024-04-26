// raylib.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <raylib.h>

#include "state.h"

int main(void) {
    enum state state = MENU;
    void (*function[])(enum state *state) = {
        [MENU] = menu,
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