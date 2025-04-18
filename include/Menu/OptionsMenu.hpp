#pragma once

#include "Interface/UiWindow.hpp"


class OptionsMenu: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        OptionsMenu(int width, int height): UiWindow(width, height)
        {   }
        OptionsMenu(OptionsMenu const& copy);

        static UiWindow* instance_;

        static bool kOk_;

        static bool  fullscreen_, vsync_, shaders_;
        static sf::String resolution_, colorDepth_, format_;
        static int   soundVolume_, musicVolume_, announcerVolume_, starfield_;
        static int   UIscale_;
};
