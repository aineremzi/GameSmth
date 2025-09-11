#include "gui.h"

bool UIElement::hovered() const{
    return CheckCollisionPointRec(GetMousePosition(), element);
}
bool UIElement::pressed() const{
    return hovered() && IsMouseButtonDown(0);
}
bool UIElement::released() const{
    return hovered() && IsMouseButtonReleased(0);
}
bool UIElement::clicked() const{
    return hovered() && IsMouseButtonPressed(0);
}
void UIElement::drawOutline(const Color color, float lineThickness) const{
    DrawRectangleLinesEx(element, lineThickness, color);
}

//Button class realization
Button::Button(float x, float y, float width, float height){
    element.x = x;
    element.y = y;
    element.width = width;
    element.height = height;
}
void Button::drawButton(const Color color, const char* buttonText, const int textFontSize, const Color textColor) const{
    DrawRectangleRec(element, color); 
    if  (buttonText){
        int buttonTextOffset = -MeasureText(buttonText, textFontSize)/2;
        int textX = element.x + element.width/2 + buttonTextOffset;
        int textY = element.y + (element.height-textFontSize)/2;
        DrawText(buttonText, textX, textY, textFontSize, textColor);
    }
}
void Button::draw(const Color color) const{
    DrawRectangleRec(element, color);
}

//CheckBox class realization
CheckBox::CheckBox(float x, float y, float width, float height, float thickness, bool checked):thick(thickness), state(checked){
    element.x = x;
    element.y = y;
    element.width = width;
    element.height = height;
}
void CheckBox::draw(Color color) const{
    if (!state){
        DrawRectangleLinesEx(element, thick, color);
    }else{
        DrawRectangleRec(element, color);
    }
}
bool CheckBox::isChecked() const{return state;}
void CheckBox::flip(){
    state = !state;
}
