#pragma once

#include "Interface/UiWindow.hpp"
#include "Weapons/weapons.hpp"
#include "Specials/specials.hpp"


class WeaponOptions: public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        WeaponOptions(int width, int height)
            : UiWindow(width, height)
        {   }

        WeaponOptions(WeaponOptions const& copy);

        static UiWindow* instance_;

        static bool kOk_;

        static bool kWeapon[weapons::All];
        static bool kSpecial[specials::All];
};
