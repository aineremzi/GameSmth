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
    SetWindowSize(Resolutions[resolution].x, Resolutions[resolution].y); //setting resolution
    SetTargetFPS(fpsLimit); //Setting fps limit
    if(vSync) // Setting vsync
        SetWindowState(FLAG_VSYNC_HINT);
    else
        ClearWindowState(FLAG_VSYNC_HINT);
    switch(fsMode){ //Setting fullscreen mode
        case WINDOWED:
            if(IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
                ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            else if(IsWindowState(FLAG_FULLSCREEN_MODE))
                ClearWindowState(FLAG_FULLSCREEN_MODE);
            break;
        case BORDERLESS:
            if(IsWindowState(FLAG_FULLSCREEN_MODE))
                ClearWindowState(FLAG_FULLSCREEN_MODE);
            if (!IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
                SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            break;
        case FULLSCREEN:
            if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
                ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            if (!IsWindowState(FLAG_FULLSCREEN_MODE))
                SetWindowState(FLAG_FULLSCREEN_MODE);
            break;
    }
    setVolume(SFXVolume); //Setting volume
}
int Settings::save(){
    std::ofstream oSettings("Settings.pref");
    if (oSettings){
        switch(resolution){
            case RESOLUTION_8K:
                oSettings << "Resolution: " << "8K";
                break;
            case RESOLUTION_4K:
                oSettings << "Resolution: " << "4K";
                break;
            case RESOLUTION_2K:
                oSettings << "Resolution: " << "2K";
                break;
            case RESOLUTION_FULLHD:
                oSettings << "Resolution: " << "FULLHD";
                break;
            case RESOLUTION_HD:
                oSettings << "Resolution: " << "HD";
                break;
            case RESOLUTION_1080I:
                oSettings << "Resolution: " << "1080I";
                break;
            case RESOLUTION_VGA:
                oSettings << "Resolution: " << "VGA";
                break;
            case RESOLUTION_SVGA:
                oSettings << "Resolution: " << "SVGA";
                break;
            case RESOLUTION_XGA:
                oSettings << "Resolution: " << "XGA";
                break;
            case RESOLUTION_W2K:
                oSettings << "Resolution: " << "W2K";
                break;
            case RESOLUTION_WFULLHD:
                oSettings << "Resolution: " << "WFULLHD";
                break;
        }    
        oSettings << "\nFullscreen: " << fsMode << "\nVsync: " << vSync << "\nFPS: " << fpsLimit << "\nVolume: " << SFXVolume << std::endl;
        oSettings.close();
        return 0;
    }
    return -1;
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
    switch (fsMode){
        case WINDOWED:
            if(IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
                ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            else if(IsWindowState(FLAG_FULLSCREEN_MODE))
                ClearWindowState(FLAG_FULLSCREEN_MODE);
            break;
        case BORDERLESS:
            if(IsWindowState(FLAG_FULLSCREEN_MODE))
                ClearWindowState(FLAG_FULLSCREEN_MODE);
            if (!IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
                SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            break;
        case FULLSCREEN:
            if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
                ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            if (!IsWindowState(FLAG_FULLSCREEN_MODE))
                SetWindowState(FLAG_FULLSCREEN_MODE);
            break;
    }
}


void getSetting(std::string value, ResolutionNames resolution){
    if (value =="1080I"){
        value = RESOLUTION_1080I;
    }else if (value == "8K"){
        value = RESOLUTION_8K;
    }else if (value == "4K"){
        value = RESOLUTION_4K;
    }else if (value == "2K"){
        value = RESOLUTION_2K;
    }else if (value == "FULLHD"){
        value = RESOLUTION_FULLHD;
    }else if (value == "HD"){
        value = RESOLUTION_HD;
    }else if (value == "WFULLHD"){
        value = RESOLUTION_WFULLHD;
    }else if (value == "W2K"){
        value = RESOLUTION_W2K;
    }else if (value == "VGA"){
        value = RESOLUTION_VGA;
    }else if (value == "SVGA"){
        value = RESOLUTION_SVGA;
    }else if (value == "XGA"){
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

