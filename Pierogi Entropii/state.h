#ifndef STATE_DEFINE
#define STATE_DEFINE

#include "isMouseInRange.h"
#include "player.h"

enum state {
    MENU,
    PLAY,
    PAUSE,
    EQUIPMENT,
    EXIT
};

inline void clickAndChangeState(enum state *state, const char *text, int frontSize, int x, int y, int incX, int incY, enum state finalState) {
    if (isMouseInRange(x, y, incX, incY, frontSize, text))
        *state = finalState;
}

void menu(enum state *state);
void play(enum state *state);
void Pause(enum state *state, enum state resumeState, RenderTexture *screenCamera1, Rectangle *splitScreenRect);
void equipment(enum state *state, enum state resumeState, RenderTexture *screenCamera1, Rectangle *splitScreenRect, struct player player);
#endif