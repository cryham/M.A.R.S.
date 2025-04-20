#pragma once

#include "Interface/UiWindow.hpp"


class ShaderError: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow()
        {   }

        static void reset();

    private:
        ShaderError(int width, int height): UiWindow(width, height)
        {   }
        ShaderError(ShaderError const& copy);

        static UiWindow* instance_;

        static bool kOk_;
};

