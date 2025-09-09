#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"

void DrawTitle(int screenWidth, int screenHeight){
    //Initializating variables
    float dist = 1 / 10.0f;
    float screenMiddle = screenHeight / 2.0f;
    float yt = screenMiddle - dist * screenHeight;
    float yb = screenMiddle + dist * screenHeight;
    //Drawing logo
    ClearBackground(BLACK);
    DrawRing(Vector2{screenWidth / 3.0f, yt}, static_cast<float>(screenWidth / 12), static_cast<float>(screenWidth / 10), 0.0f, 360.0f, 0, WHITE);
    DrawRing(Vector2{screenWidth * 2 / 3.0f, yt}, static_cast<float>(screenWidth / 12), static_cast<float>(screenWidth / 10), 0.0f, 360.0f, 0, WHITE);
    DrawCircleSector(Vector2{screenWidth * 1 / 4.0f, yt}, static_cast<float>(screenWidth / 24), -90.0f, 90.0f, 0, WHITE);
    DrawCircleSector(Vector2{screenWidth * 3 / 4.0f, yt}, static_cast<float>(screenWidth / 24), 90.0f, 270.0f, 0, WHITE);
    DrawRectangle(screenWidth / 3.0f, yb, screenWidth / 3.0f, screenHeight / 20.0f, WHITE);
}

int DrawMenu(int screenWidth, int screenHeight){
    //initializating variables
    int returnValue = -1;
    int titleFontSize = screenWidth/10;
    int titleOffset = -MeasureText("Dance on the boat", titleFontSize)/2;
    int bxm = 5;
    int buttonWidth = screenWidth/bxm;
    int buttonHeight = screenHeight/12;
    int buttonFontSize = buttonHeight/2;
    float buttonVerticalPos = screenWidth*(bxm-1)/(2*bxm);
    Button buttons[3] = {{buttonVerticalPos, screenHeight*2/6.0f, (float)buttonWidth, (float)buttonHeight}, 
                            {buttonVerticalPos, screenHeight*3/6.0f, (float)buttonWidth, (float)buttonHeight}, 
                            {buttonVerticalPos, screenHeight*4/6.0f, (float)buttonWidth, (float)buttonHeight}}; // Array with buttons
    const char* buttonTexts[3] = {"Play", "Settings", "Quit"};
    
    //Drawing menu
    ClearBackground(BLACK);
    DrawText("Dance on the boat", screenWidth/2 + titleOffset, screenHeight/12, titleFontSize, WHITE);
    
    //Drawing buttons
    for (int i = 0; i < 3; i++){
        float lineThickness = buttonWidth/100;
        if (buttons[i].pressed()){
            buttons[i].drawButton(LIGHTGRAY, buttonTexts[i], buttonFontSize, WHITE);
            buttons[i].drawOutline(BLUE, lineThickness);
        }else{
            buttons[i].drawButton(GRAY, buttonTexts[i], buttonFontSize, WHITE);
            
            //Drawing outline on hover
            if (buttons[i].hovered()){
                buttons[i].drawOutline(BLUE, lineThickness);
            }else{
                buttons[i].drawOutline(DARKGRAY, lineThickness);
            }
        }
        if (buttons[i].released()){
            returnValue = i;
        }
    }
    return returnValue;
}

void DrawSettingsMenu(int screenWidth, int screenHeight){
    int titleFontSize = screenHeight/10;
    int titleOffset = -MeasureText("Settings", titleFontSize)/2;
    ClearBackground(BLACK);
    DrawText("Settings", screenWidth/2 + titleOffset, screenHeight/12, titleFontSize, WHITE);
}