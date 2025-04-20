#pragma once

#include "Interface/UiWindow.hpp"

class TextBox;


class About: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        About(int width, int height): UiWindow(width, height)
        {   }
        About(About const& copy);

        static UiWindow* instance_;

        static bool kClose_;
        static sf::String marsName_;
};

