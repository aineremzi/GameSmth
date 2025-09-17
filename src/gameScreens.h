#pragma once
#include <map>
#include "settings.h"

enum SettingsButtons{
    SET_RESOLUTION = 0,
    SET_FULLSCREEN,
    SET_FPS,
    SET_VSYNC,
    SET_SFX
};

enum MainMenuButtons{
    MENU_PLAY = 0,
    MENU_SETTINGS,
    MENU_QUIT,
    MENU_RULES
};

void DrawTitle(const int screenWidth, const int screenHeight);
int DrawMenu(const int screenWidth, const int screenHeight); // Returns id of button chosen, or -1 if none
void DrawSettingsMenu(int screenWidth, int screenHeight, Settings settings);