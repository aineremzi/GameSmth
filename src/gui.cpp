#include "gui.h"

//Button class realization
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
        int textY = button.y + (button.height-textFontSize)/2;
        DrawText(buttonText, textX, textY, textFontSize, textColor);
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

//CheckBox class realization
CheckBox::CheckBox(float x, float y, float width, float height, float thickness, bool checked):thick(thickness), state(checked){
    box.x = x;
    box.y = y;
    box.width = width;
    box.height = height;
}
void CheckBox::drawBox(Color color){
    if (!state){
        DrawRectangleLinesEx(box, thick, color);
    }else{
        DrawRectangleRec(box, color);
    }
}
bool CheckBox::isChecked(){return state;}
bool CheckBox::hovered(){
    int mouseX = GetMouseX();          
    int mouseY = GetMouseY();
    return mouseX > box.x && mouseX < box.x + box.width && mouseY > box.y && mouseY < box.y + box.height;
}
bool CheckBox::clicked(){
    return hovered()&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
