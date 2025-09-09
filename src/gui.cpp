#include "gui.h"
#include <cmath>

Button::Button(float x, float y, float width, float height){
    button.x = x;
    button.y = y;
    button.width = width;
    button.height = height;
}
void Button::drawButton(const Color color, const char* buttonText, const int textFontSize, const Color textColor) const{
    DrawRectangleRec(button, color); 
    if  (buttonText){
        float textCoef = 5.0f;
        int buttonTextOffset = -MeasureTextEx(GetFontDefault(), buttonText, textFontSize, std::pow(button.width/200, textCoef)).x/2;
        float textX = button.x + button.width/2 + buttonTextOffset;
        float textY = button.y + (button.height-textFontSize)/2;
        DrawTextEx(GetFontDefault(), buttonText, Vector2{textX, textY}, textFontSize, std::pow(button.width/200, textCoef) ,textColor);
    }
}
bool Button::hovered() const{
    int mouseX = GetMouseX();          
    int mouseY = GetMouseY();
    return mouseX > button.x && mouseX < button.x + button.width && mouseY > button.y && mouseY < button.y + button.height;
}
bool Button::pressed() const{
    return hovered() && IsMouseButtonDown(0);
}
bool Button::released() const{
    return hovered() && IsMouseButtonReleased(0);
}
void Button::drawOutline(const Color color, float lineThickness) const{
    DrawRectangleLinesEx(button, lineThickness, color);
}

void Button::drawButton(const Color color) const{
    DrawRectangleRec(button, color);
}