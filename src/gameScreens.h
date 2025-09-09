#pragma once

enum MainMenuButtons{
    MENU_SETTINGS = 0,
    MENU_QUIT,
    MENU_PLAY,
    MENU_RULES
};

void DrawTitle(const int screenWidth, const int screenHeight);
int DrawMenu(const int screenWidth, const int screenHeight); // Returns id of button chosen, or -1 if none
void DrawSettingsMenu(int screenWidth, int screenHeight);