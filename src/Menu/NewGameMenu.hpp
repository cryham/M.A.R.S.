#pragma once

#include "Interface/UiWindow.hpp"

class Tab;


class NewGameMenu : public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow();

        static void reset();

    private:
        NewGameMenu(int width, int height): UiWindow(width, height)
        {   }
        NewGameMenu(NewGameMenu const& copy);

        static UiWindow* instance_;

        static bool kStart_, kInfo_, kCancel_, playerI_, playerII_,
                    tSB_, tDM_, tTDM_, tCK_, tGI_, tRLY_,
                    kWeaponOptions_, kMapOptions_, kGameOptions_, kBallsOptions_;

        static Tab *tabSpaceBall_, *tabDeathMatch_, *tabTeamDeathMatch_,
                   *tabCannonKeep_, *tabGraveItation_, *tabRally_;
};

