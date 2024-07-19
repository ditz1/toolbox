#include <raylib.h>
#include <chrono>
#include <string>
#include <thread>
#include <future>
#include <iostream>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void sleep_blocking(int ms, int i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    if (i == 0) {
        std::cout << "Blocking sleep done" << std::endl;
    } else {
        std::cout << "Non-blocking sleep done" << std::endl;
    }
}

std::future<void> sleep_multi(int ms, int i) {
    return std::async(std::launch::async, sleep_blocking, ms, i);
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Bench");
    SetTargetFPS(60);

    float current_time = 0.0f;
    int frame_count = 0;

    const auto start = std::chrono::steady_clock::now();
    bool blocking = false;
    std::future<void> sleep_future;

    while (!WindowShouldClose()) {
        frame_count++;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        current_time = static_cast<float>(elapsed_seconds.count());
        
        if (IsKeyPressed(KEY_SPACE)) {
            blocking = !blocking;
        }

        if (frame_count % 60 == 0) {  // Every 60 frames (roughly every second)
            if (blocking) {
                sleep_blocking(500, 0);
            } else {
                sleep_future = sleep_multi(500, 1);
            }
        }

        BeginDrawing();
        ClearBackground(BEIGE);
        
        DrawText(std::to_string(current_time).c_str(), WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 10, 20, BLACK);
        DrawText(blocking ? "Blocking" : "Non-blocking", 10, 10, 20, BLACK);
        DrawText(std::to_string(frame_count).c_str(), 10, 40, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}