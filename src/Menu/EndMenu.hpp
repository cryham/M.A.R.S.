#pragma once

#include "Interface/UiWindow.hpp"


class EndMenu: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow()
        {   }
        static void reset();

    private:
        EndMenu(int width, int height): UiWindow(width, height)
        {   }
        EndMenu(EndMenu const& copy);

        static UiWindow* instance_;

        static bool kNew_, kOptions_, kToMainMenu_, kHide_;
};

