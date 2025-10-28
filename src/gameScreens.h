#pragma once
#include <vector>
#include "gui.h"
#include "settings.h"

class Scene{
    protected:
        std::vector<UIElement*> elements;
    public:
        virtual void Draw(int screenW, int screenH) = 0;
        virtual int getState() = 0;
};

class MainMenu: public Scene{
    public:
        enum MainMenuButtons{
            MENU_PLAY = 0,
            MENU_SETTINGS,
            MENU_QUIT,
            MENU_RULES
        };
        void Draw(int screenW, int screenH) override;
        int getState() override;
};

class SettingMenu: public Scene{
    public:
        enum SettingsButtons{
            SET_RESOLUTION = 0,
            SET_FULLSCREEN,
            SET_FPS,
            SET_VSYNC,
            SET_SFX
        };
        void Draw(int screenW, int screenH) override;
        int getState() override;
};

class GameBoard: public Scene{
    public:
        void Draw(int screenW, int screenH) override;
        int getState() override;
};

class RulesMenu: public Scene{
    public:
        void Draw(int screenW, int screenH) override;
        int getState() override;
};



void DrawTitle(Settings &settings);
int DrawMenu(Settings &settings); // Returns id of button chosen, or -1 if none
void DrawSettingsMenu(Settings& settings);