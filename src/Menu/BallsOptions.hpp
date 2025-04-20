#pragma once

#include "Interface/UiWindow.hpp"


class BallsOptions : public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        BallsOptions(int width, int height): UiWindow(width, height)
        {   }
        BallsOptions(BallsOptions const& copy);

        static UiWindow* instance_;

        static bool kOk_, kDefaults_;
};
