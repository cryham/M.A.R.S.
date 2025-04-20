#pragma once

#include "Interface/UiWindow.hpp"

class TextBox;


class InfoSB: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        InfoSB(int width, int height): UiWindow(width, height)
        {   }
        InfoSB(InfoSB const& copy);

        static UiWindow* instance_;

        static bool kClose_;
};

