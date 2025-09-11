#include "../include/raylib.h"
#include <algorithm>
#include <vector>
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
    int buttonFontSize = std::min(buttonWidth/10, buttonHeight/2);
    float buttonVerticalPos = screenWidth*(bxm-1)/(2*bxm);
    std::vector<Button> buttons = {{buttonVerticalPos, screenHeight*2/6.0f, (float)buttonWidth, (float)buttonHeight}, 
                            {buttonVerticalPos, screenHeight*4/6.0f, (float)buttonWidth, (float)buttonHeight}, 
                            {buttonVerticalPos, screenHeight*5/6.0f, (float)buttonWidth, (float)buttonHeight},
                            {buttonVerticalPos, screenHeight*3/6.0f, (float)buttonWidth, (float)buttonHeight}}; // Array with buttons
    std::vector<const char*> buttonTexts = {"Play", "Settings", "Quit", "Rules"};
    
    //Drawing menu
    ClearBackground(BLACK);
    DrawText("Dance on the boat", screenWidth/2 + titleOffset, screenHeight/12, titleFontSize, WHITE);
    
    //Drawing buttons
    for (int i = 0; i < buttons.size(); i++){
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
    //Initializing variables
    int titleFontSize = screenWidth/10;
    int titleOffset = -MeasureText("Settings", titleFontSize)/2;
    int titleYCoords = screenHeight/12;
    
    int settingsFontSize = std::min(screenHeight, screenWidth)/20;
    int settingsXCoord = screenWidth/3;
    int settingsYCoef = 10;
    std::vector<std::pair<const char*, SettingsButtons>> settingsNames = {{"Resolution", SET_RESOLUTION}, {"Fullscreen", SET_FULLSCREEN}, {"Limit FPS", SET_FPS}, {"Vsync", SET_VSYNC}, {"Sound effects", SET_SFX}};
    
    float boxXCoords = screenWidth-settingsXCoord; 
    float boxSize = settingsFontSize;
    float boxThickness = boxSize/5;
    float boxYcoord = screenHeight/settingsYCoef;
    std::vector<CheckBox> settingsBoxes = {{boxXCoords - boxSize/2.0f, boxYcoord*2  + titleYCoords + titleFontSize, boxSize, boxSize, boxThickness, IsWindowState(FLAG_FULLSCREEN_MODE)},
                                           {boxXCoords - boxSize/2.0f, boxYcoord*4  + titleYCoords + titleFontSize, boxSize, boxSize, boxThickness, IsWindowState(FLAG_VSYNC_HINT)}};

    
    // std::vector<CheckBox> settingsBoxes = {{300.0f, 200.0f, 50.0f, 50.0f, 10.0f, false},
    //                                        {500.0f, 200.f, 50.0f, 50.0f, 10.0f, true}};

    //Begin Drawing
    ClearBackground(BLACK);
    DrawText("Settings", screenWidth/2 + titleOffset, titleYCoords, titleFontSize, WHITE);
    
    for (int i = 0; i < settingsNames.size(); i++){
        int settingsTextOffset = -MeasureText(settingsNames[i].first, settingsFontSize)/2;
        DrawText(settingsNames[i].first, settingsXCoord + settingsTextOffset, (screenHeight*(i+1)/settingsYCoef) + titleYCoords + titleFontSize, settingsFontSize, WHITE);
        switch (settingsNames[i].second){
            case SET_RESOLUTION:
                
                break;
            case SET_FULLSCREEN:
                if(!settingsBoxes[0].hovered()){
                    settingsBoxes[0].draw(LIGHTGRAY);
                }else{
                    settingsBoxes[0].draw(WHITE);
                }
                if(settingsBoxes[0].clicked()){
                    if(!settingsBoxes[0].isChecked()){
                        SetWindowState(FLAG_FULLSCREEN_MODE);
                        settingsBoxes[0].flip();
                    }
                    else{
                        ClearWindowState(FLAG_FULLSCREEN_MODE);
                        settingsBoxes[0].flip();
                    }
                }   
                break;
            case SET_FPS:
                
                break;
            case SET_VSYNC:
                if(!settingsBoxes[1].hovered()){
                    settingsBoxes[1].draw(LIGHTGRAY);
                }else{
                    settingsBoxes[1].draw(WHITE);
                }
                if(settingsBoxes[1].clicked()){
                    if(!settingsBoxes[1].isChecked()){
                        SetWindowState(FLAG_VSYNC_HINT);
                        settingsBoxes[1].flip();
                    }
                    else{
                        ClearWindowState(FLAG_VSYNC_HINT);
                        settingsBoxes[1].flip();
                    }
                }   
                break;
            case SET_SFX:
                
                break;
        }
    }
}