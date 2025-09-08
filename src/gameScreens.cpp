#include "../include/raylib.h"


void DrawTitle(int screenWidth, int screenHeight){
    float dist = 1 / 10.0f;
    float screenMiddle = screenHeight / 2.0f;
    float yt = screenMiddle - dist * screenHeight;
    float yb = screenMiddle + dist * screenHeight;
    ClearBackground(BLACK);
    DrawRing(Vector2{screenWidth / 3.0f, yt}, static_cast<float>(screenWidth / 12), static_cast<float>(screenWidth / 10), 0.0f, 360.0f, 0, WHITE);
    DrawRing(Vector2{screenWidth * 2 / 3.0f, yt}, static_cast<float>(screenWidth / 12), static_cast<float>(screenWidth / 10), 0.0f, 360.0f, 0, WHITE);
    DrawCircleSector(Vector2{screenWidth * 1 / 4.0f, yt}, static_cast<float>(screenWidth / 24), -90.0f, 90.0f, 0, WHITE);
    DrawCircleSector(Vector2{screenWidth * 3 / 4.0f, yt}, static_cast<float>(screenWidth / 24), 90.0f, 270.0f, 0, WHITE);
    DrawRectangle(screenWidth / 3.0f, yb, screenWidth / 3.0f, screenHeight / 20.0f, WHITE);
}