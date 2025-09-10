#pragma once
#include "../include/raylib.h"
class Button{
    private:
        Rectangle button;
    public:
        Button() = delete;
        Button(float x, float y, float width, float height);
        ~Button() = default;
        void drawButton(const Color color, const char* buttonText, const int textFontSize, const Color textColor) const;
        bool hovered() const;
        bool pressed() const;
        bool released() const;
        void drawOutline(const Color color, float lineThickness) const;
        void drawButton(const Color color) const;
};

class CheckBox{
    private:
        Rectangle box;
        float thick;
        bool state;
    public:
        CheckBox() = delete;
        CheckBox(float x, float y, float width, float height, float thickness, bool checked = false);
        ~CheckBox() = default;
        void drawBox(Color color) const;
        bool isChecked() const;
        bool hovered() const;
        bool clicked() const;
        void flip();
};

class ValueBox{

};