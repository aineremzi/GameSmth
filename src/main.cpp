#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"
#include "settings.h"
#include "gameBoard.h"

#include <vector>

#define TITLE "Dance on the boat"

int main()
{
    // Game window initialization
    Settings currSettings;
    InitWindow(currSettings.getResolution()[0], currSettings.getResolution()[1], TITLE);
    BeginDrawing();
    DrawTitle(currSettings);
    // SetWindowState(FLAG_WINDOW_RESIZABLE);
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

        // if (IsKeyPressed(KEY_F11)){
        //     if (currSettings.getFullscreenMode() == WINDOWED){
        //         currSettings.setFulscreenMode(BORDERLESS);
        //     }else{
        //         currSettings.setFulscreenMode(WINDOWED);
        //     }
        // }
        if (IsKeyDown(KEY_LEFT_ALT)){
            if(IsKeyDown(KEY_ONE))
                currState = board;
            else if(IsKeyDown(KEY_TWO))
                currState = rules;
            else if(IsKeyDown(KEY_THREE))
                currState = settings;
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
                {
                    // ClearBackground(BLACK);
                    // Button sp{currSettings.getResolution()[0]/5.0f, currSettings.getResolution()[1]/2.0f-100, currSettings.getResolution()[0]/5.0f, 200};
                    // Button ai{currSettings.getResolution()[0]*3/5.0f, currSettings.getResolution()[1]/2.0f-100, currSettings.getResolution()[0]/5.0f, 200};
                    // float lineThickness = currSettings.getResolution()[0]/5.0f/100;
                    // if (sp.pressed()){
                    //     sp.drawButton(LIGHTGRAY, "1 Player", 20, WHITE);
                    //     sp.drawOutline(BLUE, lineThickness);
                    // }else{
                    //     sp.drawButton(GRAY, "1 Player", 20, WHITE);
                        
                    //     //Drawing outline on hover
                    //     if (sp.hovered()){
                    //         sp.drawOutline(BLUE, lineThickness);
                    //     }else{
                    //         sp.drawOutline(DARKGRAY, lineThickness);
                    //     }
                    // }
                    // if (ai.pressed()){
                    //     ai.drawButton(LIGHTGRAY, "2 Players", 20, WHITE);
                    //     ai.drawOutline(BLUE, lineThickness);
                    // }else{
                    //     ai.drawButton(GRAY, "2 Players", 20, WHITE);
                        
                    //     //Drawing outline on hover
                    //     if (ai.hovered()){
                    //         ai.drawOutline(BLUE, lineThickness);
                    //     }else{
                    //         ai.drawOutline(DARKGRAY, lineThickness);
                    //     }
                    // }

                    // if (sp.released() || ai.released()){
                    //     if (sp.released()){
                    //         EndDrawing();
                    //         GameLoop(1, currSettings);
                    //         BeginDrawing();
                    //     }else{
                            EndDrawing();
                            currState = static_cast<GameStates>(GameLoop(0, currSettings));
                            BeginDrawing();
                    //     }
                    // }
                }
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
