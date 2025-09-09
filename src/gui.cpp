#include "gui.h"

Button::Button(float x, float y, float width, float height){
    button.x = x;
    button.y = y;
    button.width = width;
    button.height = height;
}
void Button::drawButton(const Color color, const char* buttonText, const int textFontSize, const Color textColor) const{
    DrawRectangleRec(button, color); 
    if  (buttonText){
        int buttonTextOffset = -MeasureText(buttonText, textFontSize)/2;
        int textX = button.x + button.width/2 + buttonTextOffset;
        int textY = button.y + button.height/3;
        DrawText(buttonText, textX, textY, textFontSize, textColor);
    }
}
bool Button::hovered() const{
    int mouseX = GetMouseX();          
    int mouseY = GetMouseY();
    return mouseX > button.x && mouseX < button.x + button.width && mouseY > button.y && mouseY < button.y + button.height;
}
bool Button::pressed() const{
    if (hovered() && IsMouseButtonReleased(0))
        return true;
    return false;
}
void Button::drawOutline(const Color color, float lineThickness) const{
    DrawRectangleLinesEx(button, lineThickness, color);
}

void Button::drawButton(const Color color) const{
    DrawRectangleRec(button, color);
}