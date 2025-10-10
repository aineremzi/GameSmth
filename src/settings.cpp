#include "settings.h"

Settings::Settings(){
    std::ifstream iSettings("Settings.pref");
    if(iSettings){
        for (std::string line; getline(iSettings, line);){
            if (line.length() > 0){
                std::string title = line.substr(0, line.find(':'));
                line = line.substr(line.find(':')+2);
                if (title == "Resolution"){
                    resolution = getSettingResolution(line);
                }else if (title == "Fullscreen"){
                    fsMode = getSettingFullscreen(line);
                }else if (title == "Vsync"){
                    vSync = getSettingVsync(line);
                }else if (title == "FPS"){
                    fpsLimit = getSettingFPS(line);
                }else if (title == "Volume"){
                    SFXVolume =getSettingVolume(line);
                }
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
void Settings::initFSMode(){
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
}
void Settings::initResolution(){
    SetWindowSize(Resolutions[resolution].x, Resolutions[resolution].y); 
}
int Settings::save(){
    std::ofstream oSettings("Settings.pref", std::ios_base::trunc);
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
            case RESOLUTION_UXGA:
                oSettings << "Resolution: " << "UXGA";
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
            default:
                oSettings << "Resolution: NaN";
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
void Settings::setVsync(bool state){
    vSync = state;
}
bool Settings::getVsync(){
    return vSync;
}


ResolutionNames getSettingResolution(std::string value){
    if (value == "UXGA"){
        return RESOLUTION_UXGA;
    }else if (value == "8K"){
        return RESOLUTION_8K;
    }else if (value == "4K"){
        return RESOLUTION_4K;
    }else if (value == "2K"){
        return RESOLUTION_2K;
    }else if (value == "FULLHD"){
        return RESOLUTION_FULLHD;
    }else if (value == "HD"){
        return RESOLUTION_HD;
    }else if (value == "WFULLHD"){
        return RESOLUTION_WFULLHD;
    }else if (value == "W2K"){
        return RESOLUTION_W2K;
    }else if (value == "VGA"){
        return RESOLUTION_VGA;
    }else if (value == "SVGA"){
        return RESOLUTION_SVGA;
    }else if (value == "XGA"){
        return RESOLUTION_XGA;
    }else{
        return DEFAULT_RESOLUTION;
    }
}

float getSettingVolume(std::string value){
    try{
        return std::stof(value);
    }
    catch(std::invalid_argument){
        return DEFAULT_VOLUME;
    }
    catch(std::out_of_range){
        return DEFAULT_VOLUME;
    }
}

bool getSettingVsync(std::string value){
    if (value == "true"){
        return true;
    }else{
        return false;
    }
}

int getSettingFPS(std::string value){
    try{
        return std::stoi(value);
    } 
    catch(std::invalid_argument){
        return DEFAULT_FPS;
    }
    catch(std::out_of_range){
        return DEFAULT_VOLUME;
    }
}

FullscreenMode getSettingFullscreen(std::string value){
    if (value == "WINDOWED"){
        return WINDOWED;
    }else if (value == "BORDERLESS"){
        return BORDERLESS;
    }else if (value == "FULLSCREEN"){
        return FULLSCREEN;
    }else{
        return DEFAULT_FULLSCREEN;
    }
}
Settings::Settings(const Settings& other):resolution(other.resolution), fsMode(other.fsMode), vSync(other.vSync), SFXVolume(other.SFXVolume), fpsLimit(other.fpsLimit){}
Settings& Settings::operator=(const Settings& other){
    if (this == &other)
        return *this;
    resolution = other.resolution;
    fsMode = other.fsMode;
    vSync = other.vSync;
    SFXVolume = other.SFXVolume;
    fpsLimit = other.fpsLimit;
    return *this;
}
Settings::Settings(Settings&& other):resolution(std::move(other.resolution)), fsMode(std::move(other.fsMode)), vSync(std::move(other.vSync)), SFXVolume(std::move(other.SFXVolume)), fpsLimit(std::move(other.fpsLimit)){}
Settings& Settings::operator=(const Settings&& other){
    if (this == &other)
        return *this;
    resolution = std::move(other.resolution);
    fsMode = std::move(other.fsMode);
    vSync = std::move(other.vSync);
    SFXVolume = std::move(other.SFXVolume);
    fpsLimit = std::move(other.fpsLimit);
    return *this;
}
