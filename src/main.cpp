#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"
#include "settings.h"
#include <iostream>

#define TITLE "Dance on the boat"

int main()
{
    // Game window initialization
    Settings currSettings;
    InitWindow(currSettings.getResolution().x, currSettings.getResolution().y, TITLE);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    currSettings.init();

    bool drawFPS = false;

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

    // Game loop
    while (!WindowShouldClose() && currState != quit)
    {
        int screenH = GetScreenHeight();
        int screenW = GetScreenWidth();
     
        if (IsKeyPressed(KEY_F3))
            drawFPS = !drawFPS;

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
            if (currSettings.getFullscreenMode() == WINDOWED)
                currSettings.setFulscreenMode(BORDERLESS);
            else
                currSettings.setFulscreenMode(WINDOWED);

        BeginDrawing();
        if (drawFPS)
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
                    case MENU_PLAY:
                        currState = board;
                        break;
                    case MENU_RULES:
                            currState = rules;
                            break;    
                    case MENU_SETTINGS:{
                        currState = settings;
                        break;
                    }
                    case MENU_QUIT:
                        currState = quit;
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
                DrawSettingsMenu(screenW, screenH, currSettings);
                break;
            case 4:
                ClearBackground(BLACK);
                DrawText("You'll get it, not stupid", 100, 540, 100, WHITE);
                break;
        }
        EndDrawing();
    }

    currSettings.save();
}