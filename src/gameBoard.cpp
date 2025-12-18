#include "gameBoard.h"
#include <iostream>
#define FIRSTC BLUE
#define SECONDC RED

int GameLoop(bool gameType, Settings& settings){
    bool turn = true;
    bool drawFPS = false;
    int lastPressed = 0;
    int chosen = -1;
    auto resolution = settings.getResolution();
    bool rolled = false;
    Color dColor = WHITE;
    Button table[24];
    int warriors[2] = {15, 15};
    int tavern[2][2] = {{0, 0}, {0, 0}};

    // board starting position
    //                1  2  3  4  5  6  7  8  9  A  B  C
    int cells[24] = { 5, 0, 0, 0,-3, 0,-5, 0, 0, 0, 0, 2,
                     -5, 0, 0, 0, 3, 0, 5, 0, 0, 0, 0,-2};


    int dice[2] = {6, 6};

    bool game = true;

    while(game){

        if (IsKeyPressed(KEY_F3))
            drawFPS = !drawFPS;
        if (drawFPS)
            DrawFPS(0,0);

        if (IsKeyPressed(KEY_F11)){
            if (settings.getFullscreenMode() == WINDOWED){
                settings.setFulscreenMode(BORDERLESS);
            }else{
                settings.setFulscreenMode(WINDOWED);
            }
        }

        settings.setResolution({GetScreenWidth(), GetScreenHeight()});  
        auto resolution = settings.getResolution();
        Color tColor = (turn)?FIRSTC:SECONDC;
        bool moveable = false;
        bool finalFase = true;

        for(int i = 0; i < 23; i++){
            if((turn && cells[i] > 0) || (!turn && cells[i] < 0)){
                finalFase = false;
                break;
            }
        }

        Button rollButton = {resolution[0]*3/8.0f, resolution[1]*17/20.0f, resolution[0]/4.0f, resolution[1]/10.0f};
        for (int i = 0; i < 24; i++){
            table[i] = {resolution[0]*(i%12)/12.0f, resolution[1]*(1+(i/12))/4.0f, resolution[0]/12.0f, resolution[1]/4.0f};
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

        if(IsKeyDown(KEY_LEFT_ALT)&&IsKeyDown(KEY_LEFT_SHIFT)&&IsKeyDown(KEY_ENTER)){
            turn = !turn;
            rolled = false;
            continue;
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
        if (!rolled && (rollButton.clicked() || IsKeyPressed(KEY_SPACE)) && lastPressed > 10){
            dColor = tColor;
            dice[0] = GetRandomValue(1, 6);
            dice[1] = GetRandomValue(1, 6);
            rolled = true;
            lastPressed = 0;
        }
        

        for(int i = 0; i < 24; i++){
            if(i == chosen){
                int pos = -1;
                for(int j = 0; j < 2; j++){
                    if (dice[j] > 0){    
                        if (turn){

                            if (i <= 11){
                                pos = (i - dice[j] >= 0)?i-dice[j]:dice[j]-i+11; 
                            }else{
                                pos = (i + dice[j] <= 23)?i+dice[j]:-1;
                            }

                            if (pos <= 23 && pos >= 0){
                                if(table[pos].clicked() && cells[pos] >= -1 && lastPressed > 10){
                                    if(cells[pos] == -1)
                                        tavern[0][1]++;
                                    cells[pos] = (cells[pos] == -1)?1:cells[pos]+1;
                                    cells[i]--;
                                    dice[j] *= -1;
                                    lastPressed = 0;
                                    chosen = -1;
                                }
                            }

                        }else{

                            if (i <= 11){
                                pos = (i + dice[j] <= 11)?i+dice[j]:-1; 
                            }else{
                                pos = (i - dice[j] >= 12)?i-dice[j]:dice[j] - i%12;
                            }

                            if (pos <= 23 && pos >= 0){
                                if(table[pos].clicked() && cells[pos] <= 1 && lastPressed > 10){
                                    if(cells[pos] == 1){
                                        tavern[0][0]++;
                                    }
                                    cells[pos] = (cells[pos] == 1)?-1:cells[pos]-1;
                                    cells[i]++;
                                    dice[j] *= -1;
                                    lastPressed = 0;
                                    chosen = -1;
                                }
                            }

                        }
                    }
                }
            }
            
            for(int j = 0; j < 2; j++){
                if(dice[j] > 0){
                    if(tavern[0][0] != 0 && cells[12 - dice[j]] >= -1 && table[12 - dice[j]].clicked()){
                        lastPressed = 0;
                        if (cells[12 - dice[j]] == -1){
                            cells[12 - dice[j]] = 1;
                            tavern[0][1]++;
                        }else{
                            cells[12 - dice[j]]++;
                        }
                        tavern[0][0]--;
                        dice[j] *= -1;
                    }else if(tavern[0][1] != 0 && cells[24 - dice[j]] <= 1 && table[24 - dice[j]].clicked()){
                        lastPressed = 0;
                        if (cells[24 - dice[j]] == 1){
                            cells[24 - dice[j]] = -1;
                            tavern[0][1]++;
                        }else{
                            cells[24 - dice[j]]--;
                        }
                        tavern[0][1]--;
                        dice[j] *= -1;
                    }
                }
            }
        }

        if(lastPressed > 10 && ((tavern[0][0] == 0 && turn) || (tavern[0][1] == 0 && !turn))){
            for(int i = 0; i < 24; i++){
                if(table[i].clicked()){
                    if(turn){
                        chosen = (cells[i] > 0)?i:-1;
                    }else{
                        chosen = (cells[i] < 0)?i:-1;
                    }
                }
            }
        }else{ 
            lastPressed++;
        }

        //Drawing the game
        BeginDrawing();

        ClearBackground(BLACK);
        if (!rolled)
            rollButton.drawButton(tColor, "Roll", 20, WHITE);

        DrawRectangle(resolution[0]/2.0f, resolution[1]*3/4.0f, resolution[0]/2.0f, resolution[1]/80.0f, BLUE);
        DrawRectangleLines(resolution[0]/2.0f, resolution[1]*3/4.0f, resolution[0]/2.0f, resolution[1]/80.0f, DARKGRAY);
        DrawRectangle(resolution[0]/2.0f, resolution[1]/4.0f-resolution[1]/80.0f, resolution[0]/2.0f, resolution[1]/80.0f, RED);
        DrawRectangleLines(resolution[0]/2.0f, resolution[1]/4.0f-resolution[1]/80.0f, resolution[0]/2.0f, resolution[1]/80.0f, DARKGRAY);

        for (int i = 0; i < 2; i++){
            DrawRectangleLines(resolution[0]*(12.75+2.5*i)/30.0f, resolution[1]/20.0f, resolution[0]/15.0f, resolution[0]/15.0f, WHITE);
            DrawText(std::to_string(abs(dice[i])).c_str(), resolution[0]*(13.25+2.5*i)/30.0f, resolution[1]*1.1/20.0f, resolution[0]/15.0f, (dice[i] > 0)?dColor:WHITE);
        }

        

        DrawText(std::to_string(warriors[0]).c_str(), resolution[0]/30.0f, resolution[1]*1.1/20.0f, resolution[0]/15.0f, FIRSTC);
        DrawText(std::to_string(warriors[1]).c_str(), resolution[0]*28/30.0f, resolution[1]*1.1/20.0f, resolution[0]/15.0f, SECONDC);

        for (int i = 0; i < 24; i++){
            table[i].draw(GRAY);
        }

        for (int i = 0; i < 24; i++){
            if(i == chosen){
                table[i].draw(LIGHTGRAY);
            }   


            if(cells[i] != 0){
                DrawRectangle(table[i].getX()+table[i].getWidth()/4, table[i].getY() + table[i].getHeight()*2/4, table[i].getWidth()/2, table[i].getWidth()/2, (cells[i] > 0)?FIRSTC:SECONDC);
                DrawText(std::to_string(abs(cells[i])).c_str(), table[i].getX()+table[i].getWidth()/2 - MeasureText(std::to_string(abs(cells[i])).c_str(), table[i].getWidth()/2)/2.0f, table[i].getY() + table[i].getHeight()/8, table[i].getWidth()/2, (cells[i] > 0)?FIRSTC:SECONDC);
            }



            bool available = false;
            if (rolled){
                int pos;
                for(int j = 0; j < 2; j++){
                    if (dice[j] > 0){
                        if (turn){

                            if(tavern[0][0] == 0){
                                if (i <= 11){
                                    pos = (i - dice[j] >= 0)?i-dice[j]:dice[j]-i+11; 
                                }else{
                                    pos = (i + dice[j] <= 23)?i+dice[j]:-1;
                                }
                                
                                if (pos <= 23 && pos >= 0){
                                    available = (cells[pos] >= -1)?true:available||false;
                                    if(i == chosen){
                                        if(cells[pos] >= -1)
                                            table[pos].draw({0,0,255,100});
                                    }
                                }
                            }else{
                                if(cells[12 - dice[j]] >= -1 && i == 12-dice[j]){
                                    table[12 - dice[j]].draw({0,0,255,100});
                                    available = true;
                                }
                            }

                        }else{

                            if(tavern[0][1] == 0){
                                if (i <= 11){
                                    pos = (i + dice[j] <= 11)?i+dice[j]:-1; 
                                }else{
                                    pos = (i - dice[j] >= 12)?i-dice[j]:dice[j] - i%12;
                                }

                                if (pos <= 23 && pos >= 0){
                                    available = (cells[pos] <= 1)?true:available||false;
                                    if(i == chosen){
                                        if(cells[pos] <= 1)
                                            table[pos].draw({255,0,0,100});
                                    }
                                }
                            }else{
                                if(cells[24 - dice[j]] <= 1 && i == 24 - dice[j]){
                                    table[24 - dice[j]].draw({255,0,0,100});
                                    available = true;
                                }
                            }

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

        std::string bText = std::to_string(tavern[0][0]).c_str();
        bText.append(" Dead");
        DrawText(bText.c_str(), resolution[0]/30.0f, resolution[1]*17/20.0f, resolution[0]/15.0f, FIRSTC);
        std::string rText = "Dead ";
        rText.append(std::to_string(tavern[0][1]).c_str());
        DrawText(rText.c_str(), resolution[0]*29/30.0f - MeasureText(rText.c_str(), resolution[0]/15.0f), resolution[1]*17/20.0f, resolution[0]/15.0f, SECONDC);

        if(!moveable && rolled){
            chosen = -1;
            if(dice[0] != dice[1]){
                turn = !turn;
            }
            rolled = false;
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