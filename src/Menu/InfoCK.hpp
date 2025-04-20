#pragma once

#include "Interface/UiWindow.hpp"

class TextBox;


class InfoCK : public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        InfoCK(int width, int height): UiWindow(width, height)
        {   }
        InfoCK(InfoCK const& copy);

        static UiWindow* instance_;

        static bool kClose_;
};
