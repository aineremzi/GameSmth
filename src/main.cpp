#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"
#include <iostream>

int main()
{

    // Game window initialization
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Dance on the boat");
    // InitWindow(800, 600, "Dance on the boat");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    int rRate = GetMonitorRefreshRate(0);
    SetTargetFPS(rRate);

    // system parametrs
    

    enum GameStates
    {
        title = 0,
        menu,
        board
    };
    GameStates currState = title;

    // Game loop
    while (!WindowShouldClose())
    {
        int screenH = GetScreenHeight();
        int screenW =GetScreenWidth();
        if (GetTime() >= 1.0f)
            currState = menu;
        BeginDrawing();
        DrawFPS(0, 0);
        switch (currState)
        {
            case 0:
                DrawTitle(screenW, screenH);
                break;
            case 1:
                DrawMenu(screenW, screenH);
                break;
        }
        EndDrawing();
    }
}