#pragma once

#include "Interface/UiWindow.hpp"


class ExitConfirm: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow()
        {   }

        static void reset();

    private:
        ExitConfirm(int width, int height): UiWindow(width, height)
        {   }
        ExitConfirm(ExitConfirm const& copy);

        static UiWindow* instance_;

        static bool kOk_, kCancel_;
};

