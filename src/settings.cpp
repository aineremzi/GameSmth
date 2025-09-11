#include "settings.h"

Settings::Settings(){
    std::ifstream iSettings("Settings.pref", std::ios::binary);
    if(iSettings){ 
        int temp;
        iSettings >> temp;
        resolution = static_cast<ResolutionNames>(temp);
        iSettings >> temp;
    }else{
        resolution = RESOLUTION_VGA;
        fsMode = WINDOWED;
        VSync = false;
        SFXVolume = 1.0f;
        fpsLimit = GetMonitorRefreshRate(0);
    }
}