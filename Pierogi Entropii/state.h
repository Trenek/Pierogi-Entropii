#ifndef STATE_DEFINE
#define STATE_DEFINE

#include "isMouseInRange.h"

enum state {
    MENU,
    PLAY,
    EXIT
};

inline void clickAndChangeState(enum state *state, const char *text, int frontSize, int x, int y, int incX, int incY, enum state finalState) {
    if (isMouseInRange(x, y, incX, incY, frontSize, text))
        *state = finalState;
}

void menu(enum state *state);
void play(enum state *state);

#endif