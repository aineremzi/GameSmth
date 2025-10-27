#pragma once
#include <map>
#include <fstream>
#include <string>
#include <array>
#include "../include/raylib.h"

#define DEFAULT_FPS 0
#define DEFAULT_RESOLUTION {800, 600}
#define DEFAULT_VOLUME 1.0f
#define DEFAULT_VSYNC true
#define DEFAULT_FULLSCREEN WINDOWED

enum FullscreenMode{
    WINDOWED = 0,
    BORDERLESS,
    FULLSCREEN
};

     
class Settings{
    private:
        std::array<int, 2> resolution;
        FullscreenMode fsMode;
        bool vSync;
        float SFXVolume;
        int fpsLimit;
    public:
        Settings();
        Settings(const Settings& other);
        Settings& operator=(const Settings& other);
        Settings(Settings&& other);
        Settings& operator=(const Settings&& other);
        ~Settings() = default;
        void init();
        void initResolution() const;
        int save();
        std::array<int, 2> getResolution() const;
        void setResolution(std::array<int, 2> Resolution);
        int getFPS() const;
        void setFPS(int& fps);
        float getVolume() const;
        void setVolume(float volume);
        FullscreenMode getFullscreenMode() const;
        void setFulscreenMode(FullscreenMode mode);
        void setVsync(bool state);
        bool getVsync() const;
};

std::array<int, 2> getSettingResolution(std::string& value);
float getSettingVolume(std::string& value);
int getSettingFPS(std::string& value);
FullscreenMode getSettingFullscreen(std::string& value);
bool getSettingVsync(std::string& value);