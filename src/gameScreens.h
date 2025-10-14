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
    MENU_SETTINGS = 0,
    MENU_QUIT,
    MENU_PLAY,
    MENU_RULES
};

void DrawTitle(Settings &settings);
int DrawMenu(Settings &settings); // Returns id of button chosen, or -1 if none
void DrawSettingsMenu(Settings& settings);