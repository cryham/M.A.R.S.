#pragma once

#include "Interface/UiWindow.hpp"

class Color3f;
class ColorPicker;
class Button;


class ColorPickerWindow: public UiWindow
{
    public:
        ColorPickerWindow (ColorPicker* parent, Color3f* color);

        void draw() const override;

        void checkWidgets() override;

        void onShow() override
        {   }
        void reset()
        {   }

    private:
        Button* Ok_;
        bool kOk_;
        ColorPicker* parent_;
        Color3f*  color_;
};
