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

class ValueBox: public UIElement{
    public:
        enum class BoxType{
            NUMBERS = 0,
            LETTERS,
            REDUCED,
            ALL
        };
        ValueBox(float x, float y, float width, float height, float thickness, std::string value, BoxType boxType);
        void draw(const Color color) const override;
        void setValue(std::string value);
        std::string getValue() const;
        bool isActive();
        void activate();
        void deactivate();
        void switchState();
    private:
        std::string _value;
        float thick;
        std::string input;
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
        const char* options;
        int currOption;
    public:
        DropDownList(float x, float y, float width, float height, float thickness, const char* values, int numOfValues, int currentOption);
        void draw(const Color color) const override; 
        int chosenOption() const;
        void setOption(int option);
        void open();
        void close();
        void switchState();
        bool isOpen() const;
};