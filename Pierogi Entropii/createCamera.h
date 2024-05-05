#include <raylib.h>

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