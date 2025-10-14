#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"
#include "settings.h"
#include <iostream>
#include <vector>

#define TITLE "Dance on the boat"

int main()
{
    // Game window initialization
    Settings currSettings;
    InitWindow(currSettings.getResolution()[0], currSettings.getResolution()[1], TITLE);
    BeginDrawing();
    DrawTitle(currSettings);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    currSettings.init();

    bool drawFPS = false;

    enum GameStates
    {
        menu =0,
        board,
        settings,
        rules,
        quit
    };
    GameStates currState = menu;

    std::vector<GameStates>rand{menu,board,settings,rules,quit};
    
    EndDrawing();
    // Game loop
    while (!WindowShouldClose() && currState != quit)
    {
        currSettings.setResolution({GetScreenWidth(), GetScreenHeight()});
     
        if (IsKeyPressed(KEY_F3))
            drawFPS = !drawFPS;

        switch (currState){
            case 0:
                SetExitKey(GetRandomValue(KEY_ZERO, KEY_NINE));
                break;
            default:
                SetExitKey(KEY_NULL);
                if (IsKeyPressed(KEY_ESCAPE))
                    currState = menu;
                break;
        }

        if (IsKeyPressed(KEY_F11)){
            if (currSettings.getFullscreenMode() == WINDOWED){
                currSettings.setFulscreenMode(BORDERLESS);
            }else{
                currSettings.setFulscreenMode(WINDOWED);
            }
        }

        BeginDrawing();
        if (drawFPS)
            DrawFPS(0, 0);
        switch (currState){
            case 0:{
                int buttonChosen = DrawMenu(currSettings);
                switch(buttonChosen){
                    case MENU_PLAY:
                        currState = rand[GetRandomValue(0,4)];
                        break;
                    case MENU_RULES:
                            currState = rand[GetRandomValue(0,4)];
                            break;    
                    case MENU_SETTINGS:{
                        currState = rand[GetRandomValue(0,4)];
                        break;
                    }
                    case MENU_QUIT:
                        currState = rand[GetRandomValue(0,4)];
                        break;
                    default:
                        break;
                }
                break;
            }
            case 1:
                ClearBackground(BLACK);
                DrawText("Here will be game board, trust me", 0, 540, 100, WHITE);
                break;
            case 2:
                DrawSettingsMenu(currSettings);
                break;
            case 3:
                ClearBackground(BLACK);
                DrawText("You'll get it, not stupid", 100, 540, 100, WHITE);
                break;
            case 4:
                CloseWindow();
                break;
        }
        EndDrawing();
    }

    currSettings.save();
}