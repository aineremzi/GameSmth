#include "../include/raylib.h"
#include "gameScreens.h"
#include <iostream>

int main()
{

    // Game window initialization
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Dance on the boat");
    // InitWindow(800, 600, "Dance on the boat");
    int rRate = GetMonitorRefreshRate(0);
    SetTargetFPS(rRate);

    // system parametrs


    enum GameStates
    {
        title = 0,
        main
    };
    GameStates currState = title;

    // Game window draw
    while (!WindowShouldClose())
    {
        BeginDrawing();
        switch (currState)
        {
        case 0:
            DrawTitle(GetScreenWidth(), GetScreenHeight());
            break;
        }
        EndDrawing();
    }
}