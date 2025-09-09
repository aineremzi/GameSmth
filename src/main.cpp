#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"
#include <iostream>

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
        settings
    };
    GameStates currState = title;

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
                switch(buttonChosen){
                    case 0:
                        currState = board;
                        break;
                    case 1:
                        currState = settings;
                        break;
                    case 2:
                        CloseWindow();
                        break;
                    default:
                        break;
                }
                break;
            }
            case 2:
                ClearBackground(BLACK);
                DrawText("Here will be game board, trust me", 0, 540, 100, WHITE);
                if (IsKeyPressed(KEY_ESCAPE))
                    currState = menu;
                break;
            case 3:
                DrawSettingsMenu(screenW, screenH);
                if (IsKeyPressed(KEY_ESCAPE))
                    currState = menu;
                break;
        }
        EndDrawing();
    }
}