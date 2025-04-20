#pragma once

#include "Interface/UiWindow.hpp"


class Connect : public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow()
        {   }

        static void reset();

    private:
        Connect(int width, int height): UiWindow(width, height)
        {   }
        Connect(Connect const& copy);

        static UiWindow* instance_;

        static bool kClose_;
};

