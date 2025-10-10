#pragma once
#include <map>
#include <fstream>
#include <string>
#include "../include/raylib.h"

#define DEFAULT_FPS 0
#define DEFAULT_RESOLUTION RESOLUTION_VGA
#define DEFAULT_VOLUME 1.0f
#define DEFAULT_VSYNC true
#define DEFAULT_FULLSCREEN WINDOWED

enum ResolutionNames{
    RESOLUTION_8K = 0, //7680x4320
    RESOLUTION_4K, //3840x2160
    RESOLUTION_2K, //2560x1440
    RESOLUTION_FULLHD, // 1920x1080
    RESOLUTION_HD, // 1280x720
    RESOLUTION_WFULLHD, // 1920x1200
    RESOLUTION_W2K, // 2560x1600
    RESOLUTION_VGA, // 640x480
    RESOLUTION_SVGA, // 800x600
    RESOLUTION_XGA, // 1024x768
    RESOLUTION_UXGA // 1600x1200
};

enum FullscreenMode{
    WINDOWED = 0,
    BORDERLESS,
    FULLSCREEN
};

     
class Settings{
    private:
        std::map<ResolutionNames, Vector2> Resolutions = {{RESOLUTION_8K, {7680, 4320}},
                                                          {RESOLUTION_4K, {3840, 2160}},
                                                          {RESOLUTION_2K, {2048, 1152}},
                                                          {RESOLUTION_FULLHD, {1920, 1080}},
                                                          {RESOLUTION_HD, {1280, 720}},
                                                          {RESOLUTION_WFULLHD, {1920, 1200}},
                                                          {RESOLUTION_W2K, {2560, 1600}},
                                                          {RESOLUTION_VGA, {640, 480}},
                                                          {RESOLUTION_SVGA, {800, 600}},
                                                          {RESOLUTION_XGA, {1024, 768}},
                                                          {RESOLUTION_UXGA, {1440, 1200}}};
        ResolutionNames resolution;
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
        void initResolution();
        void initFSMode();
        int save();
        Vector2 getResolution();
        ResolutionNames getResolutionName();
        void setResolution(ResolutionNames Resolution);
        int getFPS();
        void setFPS(int fps);
        float getVolume();
        void setVolume(float volume);
        FullscreenMode getFullscreenMode();
        void setFulscreenMode(FullscreenMode mode);
        void setVsync(bool state);
        bool getVsync();
};

ResolutionNames getSettingResolution(std::string value);
float getSettingVolume(std::string value);
int getSettingFPS(std::string value);
FullscreenMode getSettingFullscreen(std::string value);
bool getSettingVsync(std::string value);