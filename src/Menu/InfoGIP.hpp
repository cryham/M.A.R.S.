#pragma once

#include "Interface/UiWindow.hpp"

class TextBox;


class InfoGIP : public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        InfoGIP(int width, int height): UiWindow(width, height)
        {   }
        InfoGIP(InfoGIP const& copy);

        static UiWindow* instance_;

        static bool kClose_;
};
