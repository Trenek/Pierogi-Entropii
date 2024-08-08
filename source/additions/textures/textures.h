#include <raylib.h>

Texture2D *LoadPlayer(void);
Texture2D *LoadFloor(void);
Texture2D *LoadProps(void);
Texture2D *LoadClickable(void);
Texture2D *LoadCollectable(void);

void UnloadPlayer(Texture2D *texture);
void UnloadFloor(Texture2D *texture);
void UnloadProps(Texture2D *texture);
void UnloadClickable(Texture2D *texture);
void UnloadCollectable(Texture2D *texture);