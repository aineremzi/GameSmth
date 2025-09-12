#include "settings.h"

Settings::Settings(){
    std::ifstream iSettings("Settings.pref");
    if(iSettings){
        std::string line;
        getline(iSettings, line);
        line = line.substr(line.find(':')+2);
    }else{
        resolution = RESOLUTION_VGA;
        fsMode = WINDOWED;
        VSync = false;
        SFXVolume = 1.0f;
        fpsLimit = GetMonitorRefreshRate(0);
    }
}