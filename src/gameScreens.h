#pragma once

void DrawTitle(const int screenWidth, const int screenHeight);
int DrawMenu(const int screenWidth, const int screenHeight); // Returns id of button chosen, or -1 if none
void DrawSettingsMenu(int screenWidth, int screenHeight);