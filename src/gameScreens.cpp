#include "../include/raylib.h"
#include <algorithm>
#include "gameScreens.h"
#include "gui.h"
#include <string>
#include <iostream>

#define MENUBUTTONSNUM 4
#define SETTINGSNUM 5
#define G 0.001f

void DrawTitle(Settings& settings){
    //Initializating variables
    int screenHeight = settings.getResolution()[1];
    int screenWidth = settings.getResolution()[0];
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



int DrawMenu(Settings &settings){
    //initializating variables
    int screenHeight = settings.getResolution()[1];
    int screenWidth = settings.getResolution()[0];
    int returnValue = -1;
    int titleFontSize = screenWidth/10;
    int titleOffset = -MeasureText("Dance on the boat", titleFontSize)/2;
    int bxm = 5;
    int buttonWidth = screenWidth/bxm;
    int buttonHeight = screenHeight/12;
    int buttonFontSize = std::min(buttonWidth/10, buttonHeight/2);
    float buttonVerticalPos = screenWidth*(bxm-1)/(2*bxm);
    Button buttons[MENUBUTTONSNUM] = {{buttonVerticalPos, screenHeight*2/6.0f, (float)buttonWidth, (float)buttonHeight}, 
                            {buttonVerticalPos, screenHeight*4/6.0f, (float)buttonWidth, (float)buttonHeight}, 
                            {buttonVerticalPos, screenHeight*5/6.0f, (float)buttonWidth, (float)buttonHeight},
                            {buttonVerticalPos, screenHeight*3/6.0f, (float)buttonWidth, (float)buttonHeight}}; // Array with buttons
    const char* buttonTexts[MENUBUTTONSNUM] = {"Play", "Settings", "Quit", "Rules"};
    
    //Drawing menu
    ClearBackground(BLACK);
    DrawText("Dance on the boat", screenWidth/2 + titleOffset, screenHeight/12, titleFontSize, WHITE);
    
    //Drawing buttons
    for (int i = 0; i < MENUBUTTONSNUM; i++){
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



void DrawSettingsMenu(Settings &settings){
    //Initializing variables
    static Settings tempSettings = settings;
    int screenHeight = settings.getResolution()[1];
    int screenWidth = settings.getResolution()[0];

    int titleFontSize = screenWidth/10;
    int titleOffset = -MeasureText("Settings", titleFontSize)/2;
    int titleYCoords = screenHeight/12;
    
    int settingsFontSize = std::min(screenHeight, screenWidth)/20;
    int settingsXCoord = screenWidth/3;
    int settingsYCoef = 10;

    float dropDownListWidth = screenWidth/10.0f;
    float lineThickness = std::min(dropDownListWidth, (float)settingsFontSize)/5.0f;
    const char* resolutions[] = {"7680x4320", "3840x2160", "2560x1440", "1920x1080", "1280x720", "1920x1200", "2560x1600", "640x480", "800x600", "1024x768", "1600x1200"};
    const char* FSModes[] = {"Windowed", "Borderless", "Fullscreen"};
    static std::pair<const char*, UIElement*> settingsNames[SETTINGSNUM] = {{"Resolution", new DropDownList{settingsXCoord*2.0f - dropDownListWidth/2.0f, (float)(screenHeight*(1)/settingsYCoef) + titleYCoords + titleFontSize, dropDownListWidth, (float)settingsFontSize, resolutions, 11, 0}}, 
                                                                            {"Fullscreen", new DropDownList{settingsXCoord*2.0f - dropDownListWidth/2.0f, (float)(screenHeight*(2)/settingsYCoef) + titleYCoords + titleFontSize, dropDownListWidth, (float)settingsFontSize,  FSModes, 3, static_cast<int>(settings.getFullscreenMode())}}, 
                                                                            {"Limit FPS", new ValueBox{settingsXCoord*2.0f - dropDownListWidth/2.0f, (float)(screenHeight*(3)/settingsYCoef) + titleYCoords + titleFontSize, dropDownListWidth, (float)settingsFontSize, std::to_string(settings.getFPS()), ValueBox::BoxType::NUMBERS}},
                                                                            {"Vsync", new CheckBox{settingsXCoord*2.0f - settingsFontSize/2.0f, (float)(screenHeight*(4)/settingsYCoef) + titleYCoords + titleFontSize, (float)settingsFontSize, (float)settingsFontSize, lineThickness, settings.getVsync()}},
                                                                            {"Sound effects", new Slider{settingsXCoord*2.0f - dropDownListWidth/2.0f, (float)(screenHeight*(5)/settingsYCoef) + titleYCoords + titleFontSize, dropDownListWidth, (float)settingsFontSize, lineThickness, settings.getVolume()}}};
    for (int i = 0; i < SETTINGSNUM; i++){
        settingsNames[i].second->changePosition({settingsXCoord*2.0f - dropDownListWidth/2.0f, (float)(screenHeight*(i+1)/settingsYCoef) + titleYCoords + titleFontSize});
        if (i != 3)
            settingsNames[i].second->changeSize(dropDownListWidth, (float)settingsFontSize);
        else
            settingsNames[i].second->changeSize((float)settingsFontSize, (float)settingsFontSize);
    }
    static double xVelocity = 0;
    static double yVelocity = 0;
    
    //Begin Drawing
    ClearBackground(BLACK);
    DrawText("Settings", screenWidth/2 + titleOffset, titleYCoords, titleFontSize, WHITE);
    
    for (int i = 0; i < SETTINGSNUM; i++){
        int settingsTextOffset = -MeasureText(settingsNames[i].first, settingsFontSize)/2;
        DrawText(settingsNames[i].first, settingsXCoord + settingsTextOffset, (screenHeight*(i+1)/settingsYCoef) + titleYCoords + titleFontSize, settingsFontSize, WHITE);
        auto option = settingsNames[i].second;
        float outlineThickness = option->getWidth()/100.0f;
        if (i == 0){
            static Slider x = {settingsXCoord*2.0f + dropDownListWidth/4.0f + dropDownListWidth*0.5, (float)(screenHeight*(1)/settingsYCoef) + titleYCoords + titleFontSize - dropDownListWidth/2.0f, (float)settingsFontSize, dropDownListWidth, lineThickness, settings.getResolution()[0]/(float)GetMonitorWidth(GetCurrentMonitor()), Slider::SliderPosition::VERTICAL};
            static Slider y = {settingsXCoord*2.0f + dropDownListWidth/2.0f + dropDownListWidth*0.5, (float)(screenHeight*(1)/settingsYCoef) + titleYCoords + titleFontSize - dropDownListWidth/2.0f, (float)settingsFontSize, dropDownListWidth, lineThickness, settings.getResolution()[1]/(float)GetMonitorHeight(GetCurrentMonitor()), Slider::SliderPosition::VERTICAL};
            x.changePosition(settingsXCoord*2.0f + dropDownListWidth/4.0f + dropDownListWidth*0.5, (float)(screenHeight*(1)/settingsYCoef) + titleYCoords + titleFontSize - dropDownListWidth/2.0f);
            y.changePosition(settingsXCoord*2.0f + dropDownListWidth/2.0f + dropDownListWidth*0.5, (float)(screenHeight*(1)/settingsYCoef) + titleYCoords + titleFontSize - dropDownListWidth/2.0f);
            x.changeSize((float)settingsFontSize, dropDownListWidth);
            y.changeSize((float)settingsFontSize, dropDownListWidth);
            Button save {settingsXCoord*2.0f - dropDownListWidth/2.0f, (float)(screenHeight*(1)/settingsYCoef) + titleYCoords + titleFontSize, dropDownListWidth, (float)settingsFontSize};
            xVelocity-=G*GetFrameTime();
            yVelocity-=G*GetFrameTime();
            if(x.pressed()){
                xVelocity = 0;
                x.getValue();
            }
            if(y.pressed()){
                yVelocity = 0;
                y.getValue();
            }
            x.setValue(x.value()+xVelocity);
            y.setValue(y.value()+yVelocity);
            x.draw(GRAY);
            y.draw(GRAY);
            if(save.pressed()){
                save.drawButton(LIGHTGRAY, "Save", 10, WHITE);
                save.drawOutline(BLUE, outlineThickness);
            }else{
                save.drawButton(GRAY, "Save", 10, WHITE);
                save.drawOutline(DARKGRAY, outlineThickness);
            }
            if (save.released()){
                // settings.setResolution({800, 600});
                std::cout << "XXXXXXXXXXXXXXXXXXXXXX\n";
                settings.setResolution({static_cast<int>(GetMonitorWidth(0)*x.value()), static_cast<int>(GetMonitorHeight(0)*y.value())});
                // std::cout << GetMonitorWidth(0)*x.value() << " " << GetMonitorHeight(0)*y.value() << std::endl;
            }
            continue;
        }
        if (option->hovered()){
            if (option->released()){
                if (i == 0 || i == 1){
                    DropDownList* element = dynamic_cast<DropDownList*>(option);
                    if (!element->isOpen()){
                        element->switchState();
                    }
                }else if (i == 2){
                    ValueBox* element = dynamic_cast<ValueBox*>(option);
                    if(!element->isActive()){
                        element->switchState();
                        // HideCursor();
                        // DisableCursor();
                    }else{
                        std::cout << "Ready";
                        if (element->getKey() == KEY_ENTER){
                            element->deactivate();
                            EnableCursor();
                            ShowCursor();
                            int nfps = std::stoi(element->getValue());
                            settings.setFPS(nfps);
                        }
                    }
                }else if(i == 3){
                    CheckBox* element = dynamic_cast<CheckBox*>(option);
                    settings.setVsync(element->flip());
                }
            }else if(option->pressed()){
                option->draw(LIGHTGRAY);
                if (i == 4){
                    Slider* element = dynamic_cast<Slider*>(option);
                    settings.setVolume(element->getValue());
                }
            }else{
                option->draw(GRAY);
            }
            option->drawOutline(BLUE, outlineThickness);
        }else{
            option->draw(GRAY);
            option->drawOutline(DARKGRAY, outlineThickness);
        }
    }
    for (int i = 1; i < 2; i++){
        DropDownList* element = dynamic_cast<DropDownList*>(settingsNames[i].second);
        if (element->isOpen()){
            element->draw(GRAY);
            element->drawOption(GRAY, element->getWidth()/100.0f, LIGHTGRAY, BLUE);
            auto temp = element->getValue();
            if (temp != -1){
                switch(i){
                    case 0:
                        // settings.setResolution();
                        break;
                    case 1:
                        // settings.setFulscreenMode();
                        break;
                }
            }
        }
    }
}