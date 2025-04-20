#pragma once

#include "Interface/UiWindow.hpp"


class GameOptions : public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        GameOptions(int width, int height): UiWindow(width, height)
        {   }
        GameOptions(GameOptions const& copy);

        static UiWindow* instance_;

        static bool kOk_, kDefaults_;
};
