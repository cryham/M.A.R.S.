#pragma once

#include "Interface/UiWindow.hpp"

class TextBox;


class InfoTDM: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        InfoTDM(int width, int height): UiWindow(width, height)
        {   }
        InfoTDM(InfoTDM const& copy);

        static UiWindow* instance_;

        static bool kClose_;
};
