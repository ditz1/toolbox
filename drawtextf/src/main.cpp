#include <../include/raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <../include/drawtextf.hpp>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

Font f1;
Font f2;

int spacing = -0.5;
int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Bench");

    SetTargetFPS(60);
    
    f1 = LoadFont("fonts/Rubik-Medium.ttf");
    f2 = LoadFont("fonts/Rubik-Bold.ttf");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BEIGE);

            DrawTextf("Hello, World!", 300, 200, 40, spacing);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
