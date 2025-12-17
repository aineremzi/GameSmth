#include "../include/raylib.h"
#include "gameScreens.h"
#include "gui.h"
#include "settings.h"
#include <iostream>

#define TITLE "Dance on the boat"
#define FIRSTC BLUE
#define SECONDC RED

int GameLoop(bool gameType, Settings& settings);

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
        menu = 0,
        board,
        settings,
        rules,
        quit
    };
    GameStates currState = menu;
    
    EndDrawing();
    // Game loop
    while (!WindowShouldClose() && currState != quit)
    {
        currSettings.setResolution({GetScreenWidth(), GetScreenHeight()});  
     
        if (IsKeyPressed(KEY_F3))
            drawFPS = !drawFPS;

        switch (currState){
            case 0:
                SetExitKey(KEY_ESCAPE);
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
            case 1:
                {
                    ClearBackground(BLACK);
                    Button sp{currSettings.getResolution()[0]/5.0f, currSettings.getResolution()[1]/2.0f-100, currSettings.getResolution()[0]/5.0f, 200};
                    Button ai{currSettings.getResolution()[0]*3/5.0f, currSettings.getResolution()[1]/2.0f-100, currSettings.getResolution()[0]/5.0f, 200};
                    float lineThickness = currSettings.getResolution()[0]/5.0f/100;
                    if (sp.pressed()){
                        sp.drawButton(LIGHTGRAY, "1 Player", 20, WHITE);
                        sp.drawOutline(BLUE, lineThickness);
                    }else{
                        sp.drawButton(GRAY, "1 Player", 20, WHITE);
                        
                        //Drawing outline on hover
                        if (sp.hovered()){
                            sp.drawOutline(BLUE, lineThickness);
                        }else{
                            sp.drawOutline(DARKGRAY, lineThickness);
                        }
                    }
                    if (ai.pressed()){
                        ai.drawButton(LIGHTGRAY, "2 Players", 20, WHITE);
                        ai.drawOutline(BLUE, lineThickness);
                    }else{
                        ai.drawButton(GRAY, "2 Players", 20, WHITE);
                        
                        //Drawing outline on hover
                        if (ai.hovered()){
                            ai.drawOutline(BLUE, lineThickness);
                        }else{
                            ai.drawOutline(DARKGRAY, lineThickness);
                        }
                    }

                    if (sp.released() || ai.released()){
                        if (sp.released()){
                            EndDrawing();
                            GameLoop(0, currSettings);
                            BeginDrawing();
                        }else{
                            EndDrawing();
                            GameLoop(1, currSettings);
                            BeginDrawing();
                        }
                    }
                }
                break;
            case 2:
                DrawSettingsMenu(currSettings);
                break;
            case 3:
                ClearBackground(BLACK);
                DrawText("You'll get it, not stupid", 100, 540, 100, WHITE);
                break;
        }
        EndDrawing();
    }

    currSettings.save();
}

int GameLoop(bool gameType, Settings& settings){
    bool turn = true;
    auto resolution = settings.getResolution();
    bool rolled = false;
    Color dColor = WHITE;
    Button table[24];
    int warriors[2] = {15, 15};

    // board starting position
    //                1  2  3  4  5  6  7  8  9  A  B  C
    int cells[24] = { 5, 0, 0, 0,-3, 0,-5, 0, 0, 0, 0, 2,
                     -5, 0, 0, 0, 3, 0, 5, 0, 0, 0, 0,-2};


    int dice[2] = {6, 6};

    bool game = true;

    while(game){

        settings.setResolution({GetScreenWidth(), GetScreenHeight()});  
        auto resolution = settings.getResolution();
        Color tColor = (turn)?FIRSTC:SECONDC;
        bool moveable = false;

        Button rollButton = {resolution[0]*3/8.0f, resolution[1]*17/20.0f, resolution[0]/4.0f, resolution[1]/10.0f};
        for (int i = 0; i < 24; i++){
            table[i] = {resolution[0]*(i%12)/12.0f, resolution[1]*(1+(i/12))/4.0f, resolution[0]/12.0f, resolution[1]/4.0f};
        }

        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_DELETE)){
            if (IsKeyDown(KEY_ONE)){
                warriors[0] = 0;
            }else if(IsKeyDown(KEY_TWO)){
                warriors[1] = 0;
            }
        }
        if (WindowShouldClose()){
            settings.save();
            CloseWindow();
        }

        //Game logic
        if (!rolled & (rollButton.clicked() || IsKeyPressed(KEY_SPACE))){
            dColor = tColor;
            dice[0] = GetRandomValue(1, 6);
            dice[1] = GetRandomValue(1, 6);
            rolled = true;
        }

        if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_ONE)&&IsKeyUp(KEY_LEFT_SHIFT)){
            dice[0] = 1;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_TWO)&&IsKeyUp(KEY_LEFT_SHIFT)){
            dice[0] = 2;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_THREE)&&IsKeyUp(KEY_LEFT_SHIFT)){
            dice[0] = 3;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_FOUR)&&IsKeyUp(KEY_LEFT_SHIFT)){
            dice[0] = 4;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_FIVE)&&IsKeyUp(KEY_LEFT_SHIFT)){
            dice[0] = 5;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_SIX)&&IsKeyUp(KEY_LEFT_SHIFT)){
            dice[0] = 6;
        }
        if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_ONE)&&IsKeyDown(KEY_LEFT_SHIFT)){
            dice[1] = 1;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_TWO)&&IsKeyDown(KEY_LEFT_SHIFT)){
            dice[1] = 2;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_THREE)&&IsKeyDown(KEY_LEFT_SHIFT)){
            dice[1] = 3;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_FOUR)&&IsKeyDown(KEY_LEFT_SHIFT)){
            dice[1] = 4;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_FIVE)&&IsKeyDown(KEY_LEFT_SHIFT)){
            dice[1] = 5;
        }else if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_SIX)&&IsKeyDown(KEY_LEFT_SHIFT)){
            dice[1] = 6;
        }


        //Drawing the game
        BeginDrawing();

        ClearBackground(BLACK);
        if (!rolled)
            rollButton.drawButton(tColor, "Roll", 20, WHITE);

        for (int i = 0; i < 2; i++){
            DrawRectangleLines(resolution[0]*(12.75+2.5*i)/30.0f, resolution[1]/20.0f, resolution[0]/15.0f, resolution[0]/15.0f, WHITE);
            DrawText(std::to_string(dice[i]).c_str(), resolution[0]*(13.25+2.5*i)/30.0f, resolution[1]*1.1/20.0f, resolution[0]/15.0f, dColor);
        }

        DrawText(std::to_string(warriors[0]).c_str(), resolution[0]/30.0f, resolution[1]*1.1/20.0f, resolution[0]/15.0f, FIRSTC);
        DrawText(std::to_string(warriors[1]).c_str(), resolution[0]*28/30.0f, resolution[1]*1.1/20.0f, resolution[0]/15.0f, SECONDC);

        for (int i = 0; i < 24; i++){
            table[i].draw(GRAY);
            if(cells[i] != 0){
                DrawRectangle(table[i].getX()+table[i].getWidth()/4, table[i].getY() + table[i].getHeight()*2/4, table[i].getWidth()/2, table[i].getWidth()/2, (cells[i] > 0)?FIRSTC:SECONDC);
                DrawText(std::to_string(abs(cells[i])).c_str(), table[i].getX()+table[i].getWidth()/2 - MeasureText(std::to_string(abs(cells[i])).c_str(), table[i].getWidth()/2)/2.0f, table[i].getY() + table[i].getHeight()/8, table[i].getWidth()/2, (cells[i] > 0)?FIRSTC:SECONDC);
            }

            bool available = false;
            if (rolled){
                int pos;
                if (turn){
                    for(int j = 0; j < 2; j++){
                        if (i <= 11){
                            pos = (i - dice[j] >= 0)?i-dice[j]:dice[j]-i+11; 
                            if (pos <= 23 && pos >= 0)
                                available = (cells[pos] >= -1)?true||available:available||false;
                        }else{
                            pos = (i + dice[j] <= 23)?i+dice[j]:-1;
                            if (pos <= 23 && pos >= 0)
                                available = (cells[pos] >= -1)?true||available:available||false;
                        }
                    }
                }else{
                    for(int j = 0; j < 2; j++){
                        if (i <= 11){
                            pos = (i + dice[j] <= 11)?i+dice[j]:-1; 
                            if (pos <= 23 && pos >= 0)
                                available = (cells[pos] <= 1)?true||available:available||false;
                        }else{
                            pos = (i - dice[j] >= 12)?i-dice[j]:dice[j] - i%12;
                            if (pos <= 23 && pos >= 0)
                                available = (cells[pos] <= 1)?true||available:available||false;
                        }
                    }
                }
            }

            if(cells[i] > 0 && turn && rolled && available){
                table[i].drawOutline(tColor, resolution[0]/1200.0f);
            }else if (cells[i] < 0 && !turn && rolled && available){
                table[i].drawOutline(tColor, resolution[0]/1200.0f);
            }else{
                table[i].drawOutline(DARKGRAY, resolution[0]/1200.0f);
            }
            moveable = moveable || available;
        }

        if(!moveable && rolled){
            continue;
        }

        if(warriors[0] == 0){
            DrawText("Player 1 wins", resolution[0]/2.0f - MeasureText("Player 1 wins", resolution[0]/10)/2.0f, resolution[1]/2.0f, resolution[0]/10, FIRSTC);
        }else if (warriors[1] == 0){
            DrawText("Player 2 wins", resolution[0]/2.0f - MeasureText("Player 2 wins", resolution[0]/10)/2.0f, resolution[1]/2.0f- resolution[0]/20, resolution[0]/10, SECONDC);
        }

        EndDrawing();
        if (IsKeyPressed(KEY_ESCAPE))
            game = !game;
    }
    
    return 0;
}