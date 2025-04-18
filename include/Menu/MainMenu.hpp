#pragma once

#include "Interface/UiWindow.hpp"


class MainMenu: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow()
        {   }

        static void reset();

    private:
        MainMenu(int width, int height, Vector2f const& position): UiWindow(width, height, position)
        {   }
        MainMenu(MainMenu const& copy);

        static UiWindow* instance_;

        static bool kStartLocal_, kStartTut_, kStartMulti_, kJoinMulti_, kOptions_, kAbout_, kExit_;
};

