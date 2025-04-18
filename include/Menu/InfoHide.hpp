#pragma once

#include "Interface/UiWindow.hpp"

class TextBox;


class InfoHide: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow()
        {   }

        static void reset();

    private:
        InfoHide(int width, int height): UiWindow(width, height)
        {   }
        InfoHide(InfoHide const& copy);

        static UiWindow* instance_;

        static bool kOk_;
};
