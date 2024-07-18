#include <stdio.h>
#include <stdarg.h>
#include "raylib.h"
#include "raygui.h"

// requires Fontf1 to be in some file
extern Font f1;
extern Font f2;

void DrawTextf(const char* text, int posX, int posY, int fontSize, int spacing=1, Color color=RAYWHITE) {
    Font font = f1;

    Vector2 wh = MeasureTextEx(font, text, (float)fontSize, (float)spacing);
    Vector2 position = { (float)posX, (float)posY };
    DrawTextEx(font, text, position, (float)fontSize, spacing, color);
    DrawRectangleLines(posX, posY, (int)wh.x, (int)wh.y, RED);
}