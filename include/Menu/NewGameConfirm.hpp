#pragma once

#include "Interface/UiWindow.hpp"


class NewGameConfirm: public UiWindow
{
    public:
        static UiWindow* get();
        
        void checkWidgets();
        void onShow()
        {   }

        static void reset();

    private:
        NewGameConfirm(int width, int height): UiWindow(width, height)
        {   }
        NewGameConfirm(NewGameConfirm const& copy);

        static UiWindow* instance_;

        static bool kOk_, kCancel_;
};

