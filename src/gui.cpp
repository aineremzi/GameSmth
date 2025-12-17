#include "gui.h"
#include <algorithm>
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
void UIElement::changeSize(float x, float y){
    element.width = x;
    element.height = y;
}
void UIElement::changeSize(Vector2 coords){
    element.width = coords.x;
    element.height = coords.y;
}


//Button class realization
Button::Button(Rectangle button){
    element.x = button.x;
    element.y = button.y;
    element.width = button.width;
    element.height = button.height;
}
Button::Button(){
    element.x = 0;
    element.y = 0;
    element.width = 0;
    element.height = 0;
}
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
bool CheckBox::flip(){
    state = !state;
    return state;
}



//ValueBox class realization
ValueBox::ValueBox(Rectangle button, std::string value, BoxType boxType, Color textColor):_value(value), type(boxType), tColor(textColor){
    element.x = button.x;
    element.y = button.y;
    element.width = button.width;
    element.height = button.height;
}
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
void ValueBox::changeTextColor(const Color textColor){
    tColor = textColor;
}
Color ValueBox::getTextColor() const{
    return tColor;
}
int ValueBox::getKey(){
    int key = GetCharPressed();
    if(IsKeyDown(KEY_ENTER))
    return KEY_ENTER;
    while (key > 0){
        if (key >= limits[type].first && key <= limits[type].second){
            _value.push_back((char)key);
        }
        key = GetCharPressed();
    }
    if (IsKeyDown(KEY_BACKSPACE) && _value.length() != 0){
        _value.pop_back();
    }
    return key;
}


//DropDownList class realization
DropDownList::DropDownList(Rectangle button, const char** values, int numOfValues, int currentOption, Color textColor)\
                                                        :options(values), nOptions(numOfValues), currOption(currentOption), state(false), tColor(textColor){
    element.x = button.x;
    element.y = button.y;
    element.width = button.width;
    element.height = button.height;
}
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
void DropDownList::changeTextColor(const Color textColor){
    tColor = textColor;
}
Color DropDownList::getTextColor() const{
    return tColor;
}
int DropDownList::getValue(){
    for (int i = 0; i < nOptions; i++){
        Button temp = {element};
        temp.changePosition(element.x, element.y+element.height*i);
        if (temp.clicked()){
            currOption = i;
            state = !state;
            return i;
        }
    }
    return -1;
}
void DropDownList::drawOption(Color color, Color highlightColor){
    if(state){
        Button tempB(element);
        for (size_t i = 0; i < nOptions; i++){
            tempB.changePosition(element.x, element.y+element.height*i);
            if (tempB.hovered())
                tempB.draw(highlightColor);
            int fontSize = element.height/2;
            int buttonTextOffset = -MeasureText(options[i], fontSize)/2;
            int textX = element.x + element.width/2 + buttonTextOffset;
            int textY = element.y + (element.height-fontSize)/2 + element.height*i;
            DrawText(options[i], textX, textY, fontSize, tColor);
        }
    }
}
void DropDownList::drawOption(Color color, float borderSize, Color highlightColor){
    if(state){
        Button tempB(element);
        for (size_t i = 0; i < nOptions; i++){
            tempB.changePosition(element.x, element.y+element.height*i);
            if (tempB.hovered())
                tempB.drawOutline(highlightColor, borderSize);
            int fontSize = element.height/2;
            int buttonTextOffset = -MeasureText(options[i], fontSize)/2;
            int textX = element.x + element.width/2 + buttonTextOffset;
            int textY = element.y + (element.height-fontSize)/2 + element.height*i;
            DrawText(options[i], textX, textY, fontSize, tColor);
        }
    }
}
void DropDownList::drawOption(Color color, float borderSize, Color highlightColor, Color sHighlightColor){
    if(state){
        Button tempB(element);
        for (size_t i = 0; i < nOptions; i++){
            tempB.changePosition(element.x, element.y+element.height*i);
            if (tempB.hovered()){
                tempB.draw(highlightColor);
                tempB.drawOutline(sHighlightColor, borderSize);
            }
            int fontSize = element.height/2;
            int buttonTextOffset = -MeasureText(options[i], fontSize)/2;
            int textX = element.x + element.width/2 + buttonTextOffset;
            int textY = element.y + (element.height-fontSize)/2 + element.height*i;
            DrawText(options[i], textX, textY, fontSize, tColor);
        }
    }
}

//Slider class realisation
Slider::Slider(Rectangle button, float thickness, float value, SliderPosition sliderType): _value(value), thick(thickness), type(sliderType){
    element.x = button.x;
    element.y = button.y;
    element.width = button.width;
    element.height = button.height;
}
Slider::Slider(float x, float y, float width, float height, float thickness, float value, SliderPosition sliderType): _value(value), thick(thickness), type(sliderType){
    element.x = x;
    element.y = y;
    element.width = width;
    element.height = height;
}
void Slider::draw(const Color color) const{
    DrawRectangleLinesEx(element, thick, color);
    Rectangle temp = element;
    switch(type){
        case HORIZONTAL:
            temp.width*=_value;
            break;
        case VERTICAL:
            temp.height*=_value;
            temp.y += element.height - temp.height;
            break;
        case HORIZONTALREV:
            temp.width*=_value;
            temp.x += element.width - temp.width;
            break;
        case VERTICALREV:
            temp.height*=_value;
            break;
    }
    DrawRectangleRec(temp, color);
}
float Slider::value() const{
    return _value;
}
void Slider::setValue(const float newValue){
    _value = newValue;
}
float Slider::getValue(){
    switch(type){
        case HORIZONTAL:
            _value = std::max((float)0.0, std::min((float)1.0 ,(GetMousePosition().x - element.x)/element.width));
            return _value;
        case VERTICAL:
            _value = std::max((float)0.0, std::min((float)1.0 ,(float)1.0 - (GetMousePosition().y - element.y)/element.width));
            return _value;
        case HORIZONTALREV:
            _value = std::max((float)0.0, std::min((float)1.0 ,(float)1.0 - ((GetMousePosition().x - element.x)/element.width)));
            return _value;
        case VERTICALREV:
            _value = std::max((float)0.0, std::min((float)1.0 ,(GetMousePosition().y - element.y)/element.height));
            return _value;
        }
        return -1;
}