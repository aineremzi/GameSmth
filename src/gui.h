#pragma once
#include "../include/raylib.h"
class UIElement{
    protected:
        Rectangle element;
    public:
        virtual bool hovered() const;
        virtual bool pressed() const;
        virtual bool released() const;
        virtual bool clicked() const;
        virtual void drawOutline(const Color color, float lineThickness) const;
        virtual void draw(const Color color) const = 0;

};

class Button : public UIElement{
    private:
    public:
        Button() = delete;
        Button(float x, float y, float width, float height);
        ~Button() = default;
        void drawButton(const Color color, const char* buttonText, const int textFontSize, const Color textColor) const;
        void draw(const Color color) const override;
};

class CheckBox: public UIElement{
    private:
        float thick;
        bool state;
    public:
        CheckBox() = delete;
        CheckBox(float x, float y, float width, float height, float thickness, bool checked = false);
        ~CheckBox() = default;
        void draw(const Color color) const override;
        bool isChecked() const;
        void flip();
};

class ValueBox{

};