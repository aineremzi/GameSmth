#pragma once
#include <string>
#include <map>
#include "../include/raylib.h"
class UIElement{
    protected:
        Rectangle element;
    public:
        virtual bool hovered() const;
        virtual bool pressed() const;
        virtual bool released() const;
        virtual bool clicked() const;
        virtual void changePosition(float x, float y);
        virtual void changePosition(Vector2 coords);
        virtual void drawOutline(const Color color, float lineThickness) const;
        virtual float getWidth();
        virtual float getHeight();
        virtual float getX();
        virtual float getY();
        virtual void draw(const Color color) const = 0;

};

class Button : public UIElement{
    private:
    public:
        Button() = delete;
        Button(Rectangle button);
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
        CheckBox(Rectangle button, float thickness, bool checked =false);
        CheckBox(float x, float y, float width, float height, float thickness, bool checked = false);
        ~CheckBox() = default;
        void draw(const Color color) const override;
        bool isChecked() const;
        bool flip();
};

class ValueBox: public UIElement{
    public:
        enum class BoxType{
            NUMBERS = 0,
            LETTERS,
            REDUCED,
            ALL
        };
        ValueBox() = delete;
        ValueBox(Rectangle button, std::string value, BoxType boxType = BoxType::ALL, Color color = WHITE);
        ValueBox(float x, float y, float width, float height, std::string value, BoxType boxType = BoxType::ALL, Color textColor = WHITE);
        void draw(const Color color) const override;
        void setValue(std::string value);
        std::string getValue() const;
        bool isActive();
        void activate();
        std::string getValue();
        void deactivate();
        void switchState();
        void changeTextColor(const Color textColor);
        Color getTextColor() const;
    private:
        std::string _value;
        std::string input;
        Color tColor;
        bool state;
        BoxType type;
        std::map<BoxType, std::pair<int, int>> typeDesc = {{BoxType::NUMBERS, {KEY_ZERO, KEY_NINE}},
                                                           {BoxType::LETTERS, {KEY_A, KEY_Z}},
                                                           {BoxType::REDUCED, {KEY_ZERO, KEY_Z}},
                                                           {BoxType::ALL, {32, 125}}};
};

class DropDownList: public UIElement{
    private:
        bool state;
        int nOptions;
        const char** options;
        int currOption;
        Color tColor;
    public:
        DropDownList() = delete;
        DropDownList(Rectangle button, const char** values, int numOfValues, int currentOption = 0, Color textColor = WHITE);
        DropDownList(float x, float y, float width, float height, const char** values, int numOfValues, int currentOption = 0, Color textColor = WHITE);
        void draw(const Color color) const override; 
        int chosenOption() const;
        int getValue();
        void setOption(int option);
        void open();
        void close();
        void switchState();
        bool isOpen() const;
        void changeTextColor(const Color textColor);
        Color getTextColor() const;
};

class Slider: public UIElement{
    public:
        enum SliderPosition{
            HORIZONTAL = 0,
            VERTICAL,
            HORIZONTALREV,
            VERTICALREV
        };
        Slider() = delete;
        Slider(Rectangle button, float thickness, float value, SliderPosition sliderType = HORIZONTAL);
        Slider(float x, float y, float width, float height, float thickness, float value, SliderPosition sliderType = HORIZONTAL);
        void draw(const Color color) const override;
        float value() const;
        void setValue(const float newValue);
        float getValue();
    private:
        float _value;
        float thick;
        SliderPosition type;
};