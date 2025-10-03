#include "gui.h"
#include <iostream>

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
float UIElement::getWidth(){
    return element.width;
}
float UIElement::getHeight(){
    return element.height;
}
float UIElement::getX(){
    return element.x;
}
float UIElement::getY(){
    return element.y;
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
ValueBox::ValueBox(float x, float y, float width, float height, std::string value, BoxType boxType, Color textColor):_value(value), type(boxType), tColor(textColor){
    element.x = x;
    element.y = y;
    element.width = width;
    element.height = height;
}
void ValueBox::draw(const Color color) const{
        DrawRectangleRec(element, color);
        int textSize = element.height/2;
        Vector2 textPosition = {element.x + (element.width - MeasureText(_value.c_str(), textSize))/2.0f, element.y + element.height/4.0f};
        DrawText(_value.c_str(), textPosition.x, textPosition.y, textSize, tColor);
}
void ValueBox::setValue(std::string value){
    _value = value;
}
std::string ValueBox::getValue() const{
    return _value;
}
bool ValueBox::isActive(){
    return state;
}
void ValueBox::activate(){
    state = true;
}
void ValueBox::deactivate(){
    state = false;
}
void ValueBox::switchState(){
    state = !state;
}


//DropDownList class realization
DropDownList::DropDownList(float x, float y, float width, float height, const char** values, int numOfValues, int currentOption, Color textColor)\
                                                        :options(values), nOptions(numOfValues), currOption(currentOption), state(false), tColor(textColor){
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
void DropDownList::draw(Color color) const{
    if(!state){
        DrawRectangleRec(element, color);
        int fontSize = element.height/2;
        int buttonTextOffset = -MeasureText(options[currOption], fontSize)/2;
        int textX = element.x + element.width/2 + buttonTextOffset;
        int textY = element.y + (element.height-fontSize)/2;
        DrawText(options[currOption], textX, textY, fontSize, tColor);
    }else{
        Rectangle temp = {element.x, element.y, element.width, element.height*nOptions};
        DrawRectangleRec(temp, color);
        for (size_t i = 0; i < nOptions; i++){
            int fontSize = element.height/2;
            int buttonTextOffset = -MeasureText(options[i], fontSize)/2;
            int textX = element.x + element.width/2 + buttonTextOffset;
            int textY = element.y + (element.height-fontSize)/2 + element.height*i;
            DrawText(options[i], textX, textY, fontSize, tColor);
        }
    }
}
