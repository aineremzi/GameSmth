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
void UIElement::changePosition(float x, float y){
    element.x = x;
    element.y = y;
}
void UIElement::changePosition(Vector2 coords){
    element.x = coords.x;
    element.y = coords.y;
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



//ValueBox class realization
ValueBox::ValueBox(float x, float y, float width, float height, float thickness, std::string value):thick(thickness), _value(value){
    element.x = x;
    element.y = y;
    element.width = width;
    element.height = height;
}
void ValueBox::draw(const Color color) const{

}
void ValueBox::setValue(std::string value){
    _value = value;
}
std::string ValueBox::getValue() const{
    return _value;
}



//DropDownList class realization
DropDownList::DropDownList(float x, float y, float width, float height, float thickness, std::vector<std::string> values, int currentOption):options(values), currOption(currentOption), state(false){
    element.x = x;
    element.y = y;
    element.width = width;
    element.height = height;
}
int DropDownList::chosenOption() const{
    return currOption;
}
void DropDownList::setOption(int option){
    currOption = option;
}
void DropDownList::open(){
    state = true;
}
void DropDownList::close(){
    state = false;
}
void DropDownList::switchState(){
    state = !state;
}
bool DropDownList::isOpen() const{
    return state;
}
