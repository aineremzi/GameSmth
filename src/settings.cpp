#include "settings.h"


Settings::Settings(){
    std::ifstream iSettings("Settings.pref");
    resolution = DEFAULT_RESOLUTION;
    fsMode = DEFAULT_FULLSCREEN;
    vSync = DEFAULT_VSYNC;
    SFXVolume = DEFAULT_VOLUME;
    fpsLimit = DEFAULT_FPS;
    if(iSettings){
        for (std::string line; getline(iSettings, line);){
            if (line.length() > 1){
                std::string title = line.substr(0, line.find(':'));
                if (line.find(':')+2 < line.length())
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
    }
    iSettings.close();
}


void Settings::init(){
    SetWindowSize(resolution[0], resolution[1]); //setting resolution
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
    std::ofstream oSettings("Settings.pref", std::ios_base::trunc);
    if (oSettings){   
        oSettings << "Resolution: " << resolution[0] << "x" << resolution[1] << "\nFullscreen: " << fsMode << "\nVsync: " << vSync << "\nFPS: " << fpsLimit << "\nVolume: " << SFXVolume << std::endl;
        oSettings.close();
        return 0;
    }
    return -1;
}
std::array<int, 2> Settings::getResolution() const{
    return resolution;
}
void Settings::setResolution(std::array<int, 2> newResolution){
    resolution = newResolution;
    SetWindowSize(resolution[0], resolution[1]);
}
int Settings::getFPS() const{
    return fpsLimit;
}
void Settings::setFPS(int& fps){
    fpsLimit = fps;
    SetTargetFPS(fps);
}
float Settings::getVolume() const{
    return SFXVolume;
}
void Settings::setVolume(float volume){
    SFXVolume = volume;
}
FullscreenMode Settings::getFullscreenMode() const{
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
bool Settings::getVsync() const{
    return vSync;
}


std::array<int, 2> getSettingResolution(std::string& value){
    try{
        int x = std::stoi(value.substr(0, value.find('x')));
        int y = std::stoi(value.substr(value.find('x')+1));
        if (x == 0 ||  y == 0)
            return DEFAULT_RESOLUTION;
        std::array<int, 2> res = {x, y};
        return res;
    } 
    catch(std::invalid_argument){
        return DEFAULT_RESOLUTION;
    }
    catch(std::out_of_range){
        return DEFAULT_RESOLUTION;
    }
}

float getSettingVolume(std::string& value){
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

bool getSettingVsync(std::string& value){
    if (value == "true"){
        return true;
    }else{
        return false;
    }
}

int getSettingFPS(std::string& value){
    try{
        return std::stoi(value);
    } 
    catch(std::invalid_argument){
        return DEFAULT_FPS;
    }
    catch(std::out_of_range){
        return DEFAULT_FPS;
    }
}

FullscreenMode getSettingFullscreen(std::string& value){
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
