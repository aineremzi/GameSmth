#pragma once
#include <map>
#include <vector>
#include <fstream>
#include "../include/raylib.h"

enum ResolutionNames{
    RESOLUTION_8K = 0,
    RESOLUTION_4K,
    RESOLUTION_2K,
    RESOLUTION_FULLHD,
    RESOLUTION_HD,
    RESOLUTION_WFULLHD,
    RESOLUTION_W2K,
    RESOLUTION_VGA,
    RESOLUTION_SVGA,
    RESOLUTION_XGA,
    RESOLUTION_1080I
};

enum FullscreenMode{
    WINDOWED = 0,
    BORDERLESS,
    FULLSCREEN
};

std::map<ResolutionNames, std::vector<int>> Resolutions = {{RESOLUTION_8K, {7680, 4320}},
                                                           {RESOLUTION_4K, {3840, 2160}},
                                                           {RESOLUTION_2K, {2048, 1152}},
                                                           {RESOLUTION_FULLHD, {1920, 1080}},
                                                           {RESOLUTION_HD, {1280, 720}},
                                                           {RESOLUTION_WFULLHD, {1920, 1200}},
                                                           {RESOLUTION_W2K, {2560, 1600}},
                                                           {RESOLUTION_VGA, {640, 480}},
                                                           {RESOLUTION_SVGA, {800, 600}},
                                                           {RESOLUTION_XGA, {1024, 768}},
                                                           {RESOLUTION_1080I, {1440, 1200}}};
                                                           

class Settings{
    private:
        ResolutionNames resolution;
        FullscreenMode fsMode;
        bool VSync;
        float SFXVolume;
        int fpsLimit;
    public:
        Settings();
        ~Settings() = default;
        void init();
        int save();
};