#pragma once

#include "Interface/UiWindow.hpp"


class EnterName : public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        EnterName(int width, int height): UiWindow(width, height)
        {   }
        EnterName(EnterName const& copy);

        static UiWindow* instance_;

        static bool kOk_;
};

