#pragma once

#include "Interface/UiWindow.hpp"


class ToMainConfirm: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow()
        {   }

        static void reset();

    private:
        ToMainConfirm(int width, int height): UiWindow(width, height)
        {   }
        ToMainConfirm(ToMainConfirm const& copy);

        static UiWindow* instance_;

        static bool kOk_, kCancel_;
};

