#pragma once

#include "Interface/UiWindow.hpp"


class PauseMenu: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow()
        {   }

        static void reset();

    private:
        PauseMenu(int width, int height): UiWindow(width, height)
        {   }
        PauseMenu(PauseMenu const& copy);

        static UiWindow* instance_;

        static bool kResume_, kNew_,
            kOptions_, kMapOptions_, kGameOptions_,
            kToMainMenu_, kHide_;
};
