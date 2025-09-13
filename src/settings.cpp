#include "settings.h"

Settings::Settings(){
    std::ifstream iSettings("Settings.pref");
    if(iSettings){
        for (std::string line; getline(iSettings, line);){
            std::string title = line.substr(0, line.find(':'));
            line = line.substr(line.find(':')+2);
            if (title == "Resolution:"){
                getSetting(line, resolution);
            }else if (title == "Fullscreen:"){
                getSetting(line, fsMode);
            }else if (title == "Vsync:"){
                getSetting(line, vSync);
            }else if (title == "FPS:"){
                getSetting(line, fpsLimit);
            }else if (title == "Volume:"){
                getSetting(line, SFXVolume);
            }
        }
        iSettings.close();
    }else{
        resolution = DEFAULT_RESOLUTION;
        fsMode = DEFAULT_FULLSCREEN;
        vSync = DEFAULT_VSYNC;
        SFXVolume = DEFAULT_VOLUME;
        fpsLimit = DEFAULT_FPS;
    }
}
void Settings::init(){
    
}
int Settings::save(){
    std::ofstream oSettings("Settings.pref");
    if (oSettings){    
        oSettings << "Resolution: " << resolution << "\nFullscreen: " << fsMode << "\nVsync: " << vSync << "\nFPS: " << fpsLimit << "\nVolume: " << SFXVolume << std::endl;
        oSettings.close();
    }
}
Vector2 Settings::getResolution(){
    return Resolutions[resolution];
}
ResolutionNames Settings::getResolutionName(){
    return resolution;
}
void Settings::setResolution(ResolutionNames newResolution){
    resolution = newResolution;
}
int Settings::getFPS(){
    return fpsLimit;
}
void Settings::setFPS(int fps){
    fpsLimit = fps;
}
float Settings::getVolume(){
    return SFXVolume;
}
void Settings::setVolume(float volume){
    SFXVolume = volume;
}
FullscreenMode Settings::getFullscreenMode(){
    return fsMode;
}
void Settings::setFulscreenMode(FullscreenMode mode){
    fsMode = mode;
}


void getSetting(std::string value, ResolutionNames resolution){
    if (value =="RESOLUTION_1080I"){
        value = RESOLUTION_1080I;
    }else if (value == "RESOLUTION_8K"){
        value = RESOLUTION_8K;
    }else if (value == "RESOLUTION_4K"){
        value = RESOLUTION_4K;
    }else if (value == "RESOLUTION_2K"){
        value = RESOLUTION_2K;
    }else if (value == "RESOLUTION_FULLHD"){
        value = RESOLUTION_FULLHD;
    }else if (value == "RESOLUTION_HD"){
        value = RESOLUTION_HD;
    }else if (value == "RESOLUTION_WFULLHD"){
        value = RESOLUTION_WFULLHD;
    }else if (value == "RESOLUTION_W2K"){
        value = RESOLUTION_W2K;
    }else if (value == "RESOLUTION_VGA"){
        value = RESOLUTION_VGA;
    }else if (value == "RESOLUTION_SVGA"){
        value = RESOLUTION_SVGA;
    }else if (value == "RESOLUTION_XGA"){
        value = RESOLUTION_XGA;
    }else{
        value = DEFAULT_RESOLUTION;
    }
}

void getSetting(std::string value, float volume){
    try{
        volume = std::stof(value);
    }
    catch(std::invalid_argument){
        volume = DEFAULT_VOLUME;
    }
}

void getSetting(std::string value, bool vsync){
    if (value == "true"){
        vsync = true;
    }else{
        vsync = false;
    }
}

void getSetting(std::string value, int fps){
    try{
        fps = std::stoi(value);
    } 
    catch(std::invalid_argument){
        fps = DEFAULT_FPS;
    }
}

void getSetting(std::string value, FullscreenMode fullscreen){
    if (value == "WINDOWED"){
        value = WINDOWED;
    }else if (value == "BORDERLESS"){
        value = BORDERLESS;
    }else if (value == "FULLSCREEN"){
        value = FULLSCREEN;
    }else{
        value = DEFAULT_FULLSCREEN;
    }
}

