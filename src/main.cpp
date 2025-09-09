#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"
#include <iostream>

#define ESC_KEY 256

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
        board,
        settings
    };
    GameStates currState = title;

    // Game loop
    while (!WindowShouldClose())
    {
        int screenH = GetScreenHeight();
        int screenW =GetScreenWidth();
     
        switch (currState){
            case 1:
                SetExitKey(ESC_KEY);
                break;
            default:
                SetExitKey(KEY_NULL);
                break;
        }

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
                break;
            case 3:
                DrawSettingsMenu(screenW, screenH);
                if (IsKeyPressed(ESC_KEY))
                    currState = menu;
                break;
        }
        EndDrawing();
    }
}