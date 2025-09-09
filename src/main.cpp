#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"
#include <iostream>

int main()
{

    // Game window initialization
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Dance on the boat");
    // InitWindow(800, 600, "Dance on the boat");
    int rRate = GetMonitorRefreshRate(0);
    SetTargetFPS(rRate);

    // system parametrs
    int screenH = GetScreenHeight();
    int screenW =GetScreenWidth();

    enum GameStates
    {
        title = 0,
        menu,
        board
    };
    GameStates currState = title;

    // Game window draw
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawFPS(0, 0);
        switch (currState)
        {
            case 0:
                DrawTitle(screenW, screenH);
                if (GetTime() >= 1.0f)
                    currState = menu;
                break;
            case 1:
                //initializating variables
                int titleFontSize = screenH/10;
                int titleOffset = -MeasureText("Dance on the boat", titleFontSize)/2;
                int bxm = 5;
                int buttonWidth = screenW/bxm;
                int buttonHeight = screenH/12;
                int buttonFontSize = buttonHeight/3;
                float buttonVerticalPos = screenW*(bxm-1)/(2*bxm);
                Button buttons[3] = {{buttonVerticalPos, screenH*2/6.0f, (float)buttonWidth, (float)buttonHeight}, 
                                        {buttonVerticalPos, screenH*3/6.0f, (float)buttonWidth, (float)buttonHeight}, 
                                        {buttonVerticalPos, screenH*4/6.0f, (float)buttonWidth, (float)buttonHeight}}; // Array with buttons
                const char* buttonTexts[3] = {"Play", "Settings", "Quit"};
                
                //Drawing menu
                ClearBackground(BLACK);
                DrawText("Dance on the boat", screenW/2 + titleOffset, screenH/12, titleFontSize, WHITE);
                
                //Drawing buttons
                for (int i = 0; i < 3; i++){
                    buttons[i].drawButton(GRAY, buttonTexts[i], buttonFontSize, WHITE);
                    
                    //Drawing outline on hover
                    if (buttons[i].hovered()){
                        float lineThickness = buttonWidth/100;
                        buttons[i].drawOutline(BLUE, lineThickness);
                    }
                }
        }
        EndDrawing();
    }
}