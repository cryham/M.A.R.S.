#pragma once

#include "Interface/UiWindow.hpp"


class MapOptions: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        MapOptions(int width, int height)
            : UiWindow(width, height)
        {   }

        MapOptions(MapOptions const& copy);

        static UiWindow* instance_;

        static bool kOk_;
        static bool kDefaults_;

        static const int kMapSizes_ = 7;
        static bool kMapSize_[kMapSizes_];
};
