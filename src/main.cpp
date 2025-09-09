#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"
#include <iostream>
#include <vector>

int main()
{
    // Game window initialization
    std::cout << GetCurrentMonitor() << std::endl;
    InitWindow(800, 600, "Dance on the boat");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    int rRate = GetMonitorRefreshRate(0);
    SetTargetFPS(rRate);

    // system parametrs
    

    enum GameStates
    {
        title = 0,
        menu,
        board,
        settings,
        rules,
        quit
    };
    GameStates currState = title;

    std::vector<GameStates>rand{title,menu,board,settings,rules,quit};

    // Game loop
    while (!WindowShouldClose())
    {
        int screenH = GetScreenHeight();
        int screenW = GetScreenWidth();
     
        switch (currState){
            case 1:
                SetExitKey(KEY_ESCAPE);
                break;
            default:
                SetExitKey(KEY_NULL);
                if (IsKeyPressed(KEY_ESCAPE))
                    currState = menu;
                break;
        }

        if (IsKeyPressed(KEY_F11))
            if (!IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
                SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            else
                ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);

        BeginDrawing();
        DrawFPS(0, 0);
        switch (currState)
        {
            case 0:
                DrawTitle(screenW, screenH);
                if (GetTime() >= 1.0f)
                    currState = menu;
                break;
            case 1:{
                int buttonChosen = DrawMenu(screenW, screenH);
                if (buttonChosen != -1){
                    currState = rand[GetRandomValue(0, 5)];
                }
                break;
            }
            case 2:
                ClearBackground(BLACK);
                DrawText("Here will be game board, trust me", 0, 540, 100, WHITE);
                break;
            case 3:
                DrawSettingsMenu(screenW, screenH);
                break;
            case 4:
                ClearBackground(BLACK);
                DrawText("You'll get it, not stupid", 100, 540, 100, WHITE);
                break;
            case 5:
                CloseWindow();
                break;
        }
        EndDrawing();
    }
}