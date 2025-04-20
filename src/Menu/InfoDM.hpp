#pragma once

#include "Interface/UiWindow.hpp"

class TextBox;


class InfoDM : public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        InfoDM(int width, int height): UiWindow(width, height)
        {   }
        InfoDM(InfoDM const& copy);

        static UiWindow* instance_;

        static bool kClose_;
};
