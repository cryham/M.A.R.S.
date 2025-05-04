#include "Menu/NewGameMenu.hpp"

#include "Media/text.hpp"
#include "Media/music.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/Tab.hpp"
#include "Interface/TabList.hpp"
#include "Interface/RadioGroup.hpp"
#include "Interface/RadioButton.hpp"
#include "Interface/Slider.hpp"
#include "Interface/Checkbox.hpp"
// #include "Interface/Line.hpp"
#include "Interface/LabeledBox.hpp"

#include "Games/games.hpp"
#include "System/settings.hpp"
#include "Menu/menus.hpp"
#include "Locales/locales.hpp"

#include "Menu/InfoSB.hpp"
#include "Menu/InfoDM.hpp"
#include "Menu/InfoTDM.hpp"
#include "Menu/InfoCK.hpp"
#include "Menu/InfoGIP.hpp"

#include "Menu/WeaponOptions.hpp"
#include "Menu/MapOptions.hpp"
#include "Menu/GameOptions.hpp"
#include "Menu/BallsOptions.hpp"


UiWindow* NewGameMenu::instance_ = nullptr;

bool NewGameMenu::kStart_(false);
bool NewGameMenu::kInfo_(false);
bool NewGameMenu::kCancel_(false);

bool NewGameMenu::playerI_(false);
bool NewGameMenu::playerII_(false);

bool NewGameMenu::tSB_(false);
bool NewGameMenu::tDM_(false);
bool NewGameMenu::tTDM_(false);
bool NewGameMenu::tCK_(false);
bool NewGameMenu::tGI_(false);
bool NewGameMenu::tRLY_(false);

Tab* NewGameMenu::tabSpaceBall_ = nullptr;
Tab* NewGameMenu::tabDeathMatch_ = nullptr;
Tab* NewGameMenu::tabTeamDeathMatch_ = nullptr;
Tab* NewGameMenu::tabCannonKeep_ = nullptr;
Tab* NewGameMenu::tabGraveItation_ = nullptr;
Tab* NewGameMenu::tabRally_ = nullptr;

bool NewGameMenu::kWeaponOptions_(false);
bool NewGameMenu::kMapOptions_(false);
bool NewGameMenu::kGameOptions_(false);
bool NewGameMenu::kBallsOptions_(false);


UiWindow* NewGameMenu::get()
{
    if (!instance_)
    {
        instance_ = new NewGameMenu(580, 350);
        instance_->addWidget(new Label(locales::getLocale(locales::NewGame), TEXT_ALIGN_LEFT,
			Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));

        Button* btnOk = new Button(locales::getLocale(locales::Start), "", &kStart_,
			Vector2f(475,320), 90, 20);
        instance_->addWidget(btnOk);
        btnOk->setFocus(btnOk, false);
        instance_->addWidget(new Button(locales::getLocale(locales::Cancel), "", &kCancel_,
			Vector2f(375,320), 90, 20));

        //  bottom buttons
        int y2 = 268, y2w = 212;
        instance_->addWidget(new Button(locales::getLocale(locales::Info), "", &kInfo_,
			Vector2f(20-4,y2), 90, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::MapOptions), "", &kMapOptions_,
			Vector2f(250-4,y2), 120, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::GameOptions), "", &kGameOptions_,
			Vector2f(380-4,y2), 120, 20));

        TabList* tabList    = new TabList(Vector2f(10,75), 560, 220);
        tabSpaceBall_       = new Tab("SpaceBall", 90,  &tSB_);
        tabDeathMatch_      = new Tab("DeathMatch", 100, &tDM_);
        tabTeamDeathMatch_  = new Tab("Team-DeathMatch", 120, &tTDM_);
        tabCannonKeep_      = new Tab("CannonKeep", 100, &tCK_);
        tabGraveItation_    = new Tab("Grave-Itation Pit", 125, &tGI_);
        tabRally_           = new Tab("Rally", 80, &tRLY_);  //-

        //  Space Ball  ----
        int x = 10, y1 = 30, y = y1, yadd = 20;
        tabSpaceBall_->addWidget(new LabeledBox(locales::getLocale(locales::LeftTeam),
			Vector2f(10, y), 250, 80));
        tabSpaceBall_->addWidget(new LabeledBox(locales::getLocale(locales::RightTeam),
			Vector2f(300, y), 250, 80));  y += yadd*3/2;
        RadioGroup* player1Group = new RadioGroup();
            player1Group->addRadioButton(new RadioButton(settings::sPlayer1Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer1teamL,
			Vector2f(20, y), 80, true));
            player1Group->addRadioButton(new RadioButton(settings::sPlayer1Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer1teamR,
			Vector2f(310, y), 80, true));
        tabSpaceBall_->addWidget(player1Group);
        RadioGroup* player2Group = new RadioGroup();
            player2Group->addRadioButton(new RadioButton(settings::sPlayer2Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer2teamL,
			Vector2f(120, y), 80, true));
            player2Group->addRadioButton(new RadioButton(settings::sPlayer2Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer2teamR,
			Vector2f(410, y), 80, true));  y += yadd;
        
        tabSpaceBall_->addWidget(player2Group);
        tabSpaceBall_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsLeft, 0, 20, 1,
			Vector2f(20, y), 230, 120, true));
        tabSpaceBall_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsRight, 0, 20, 1,
			Vector2f(310, y), 230, 120, true));  y += yadd*2;
        tabSpaceBall_->addWidget(new LabeledBox(locales::getLocale(locales::GameOptions),
			Vector2f(10, y), 540, 100));  y += yadd*3/2;

        tabSpaceBall_->addWidget(new Slider(locales::Pointlimit, locales::ttPointLimitTeam,
			&settings::iPointLimitSB, 1, 260, 1,
			Vector2f(20, y), 520, 270, true));  y += yadd;
            
        tabSpaceBall_->addWidget(new Button(locales::getLocale(locales::BallsOptions), "", &kBallsOptions_,
			Vector2f(20, y), 120, 20));  y += yadd;
        tabSpaceBall_->addWidget(new Button(locales::getLocale(locales::WeaponOptions), "", &kWeaponOptions_,
			Vector2f(110,y2w), 120, 20));

        //  Death Match  ----
        y = y1;
        tabDeathMatch_->addWidget(new LabeledBox(locales::getLocale(locales::PlayerOptions),
			Vector2f(10, y), 540, 80));  y += yadd*3/2;
        tabDeathMatch_->addWidget(new Checkbox(settings::sPlayer1Name, locales::getLocale(locales::ttPlayersWho), &playerI_,
			Vector2f(20, y), 100));
        tabDeathMatch_->addWidget(new Checkbox(settings::sPlayer2Name, locales::getLocale(locales::ttPlayersWho), &playerII_,
			Vector2f(310, y), 100));  y += yadd;
        tabDeathMatch_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsDeath, 0, 80, 1,
			Vector2f(20, y), 520, 270, true));  y += yadd*2;

        tabDeathMatch_->addWidget(new LabeledBox(locales::getLocale(locales::GameOptions),
			Vector2f(10, y), 540, 100));  y += yadd*3/2;
        tabDeathMatch_->addWidget(new Slider(locales::Fraglimit, locales::ttPointLimitTeam,
			&settings::iPointLimitDM, 1, 400, 1,
			Vector2f(20, y), 520, 270, true));
        
        tabDeathMatch_->addWidget(new Button(locales::getLocale(locales::WeaponOptions), "", &kWeaponOptions_,
			Vector2f(110,y2w), 120, 20));

        //  Team Death Match  ----
        y = y1;
        tabTeamDeathMatch_->addWidget(new LabeledBox(locales::getLocale(locales::LeftTeam),
			Vector2f(10, 30), 250, 80));
        tabTeamDeathMatch_->addWidget(new LabeledBox(locales::getLocale(locales::RightTeam),
			Vector2f(300, 30), 250, 80));
        RadioGroup* player1Group2 = new RadioGroup();
            player1Group2->addRadioButton(new RadioButton(settings::sPlayer1Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer1teamL,
			Vector2f(20,60), 80, true));
            player1Group2->addRadioButton(new RadioButton(settings::sPlayer1Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer1teamR,
			Vector2f(310,60), 80, true));
        tabTeamDeathMatch_->addWidget(player1Group2);
        RadioGroup* player2Group2 = new RadioGroup();
            player2Group2->addRadioButton(new RadioButton(settings::sPlayer2Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer2teamL,
			Vector2f(120,60), 80, true));
            player2Group2->addRadioButton(new RadioButton(settings::sPlayer2Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer2teamR,
			Vector2f(410,60), 80, true));
        tabTeamDeathMatch_->addWidget(player2Group2);
        tabTeamDeathMatch_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsLeft, 0, 30, 1,
			Vector2f(20,80), 230, 120, true));
        tabTeamDeathMatch_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsRight, 0, 30, 1,
			Vector2f(310,80), 230, 120, true));
        tabTeamDeathMatch_->addWidget(new LabeledBox(locales::getLocale(locales::GameOptions),
			Vector2f(10,120), 540, 100));
        
        tabTeamDeathMatch_->addWidget(new Slider(locales::Fraglimit, locales::ttPointLimitTeam,
			&settings::iPointLimitTDM, 1, 400, 1,
			Vector2f(20,150), 520, 270, true));
        tabTeamDeathMatch_->addWidget(new Button(locales::getLocale(locales::WeaponOptions), "", &kWeaponOptions_,
			Vector2f(110,y2w), 120, 20));

        //  Cannon Keep  ----
        tabCannonKeep_->addWidget(new LabeledBox(locales::getLocale(locales::LeftTeam),
			Vector2f(10, 30), 250, 80));
        tabCannonKeep_->addWidget(new LabeledBox(locales::getLocale(locales::RightTeam),
			Vector2f(300, 30), 250, 80));
        RadioGroup* player1Group3 = new RadioGroup();
            player1Group3->addRadioButton(new RadioButton(settings::sPlayer1Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer1teamL,
			Vector2f(20,60), 80, true));
            player1Group3->addRadioButton(new RadioButton(settings::sPlayer1Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer1teamR,
			Vector2f(310,60), 80, true));
        tabCannonKeep_->addWidget(player1Group3);
        RadioGroup* player2Group3 = new RadioGroup();
            player2Group3->addRadioButton(new RadioButton(settings::sPlayer2Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer2teamL,
			Vector2f(120,60), 80, true));
            player2Group3->addRadioButton(new RadioButton(settings::sPlayer2Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer2teamR,
			Vector2f(410,60), 80, true));
        tabCannonKeep_->addWidget(player2Group3);
        tabCannonKeep_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsLeft, 0, 20, 1,
			Vector2f(20,80), 230, 120, true));
        tabCannonKeep_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsRight, 0, 20, 1,
			Vector2f(310,80), 230, 120, true));
        tabCannonKeep_->addWidget(new LabeledBox(locales::getLocale(locales::GameOptions),
			Vector2f(10,120), 540, 100));
        
        tabCannonKeep_->addWidget(new Slider(locales::Pointlimit, locales::ttPointLimitTeam,
			&settings::iPointLimitCK, 1, 50, 1,
			Vector2f(20,150), 520, 270, true));
        tabCannonKeep_->addWidget(new Button(locales::getLocale(locales::WeaponOptions), "", &kWeaponOptions_,
			Vector2f(110,y2w), 120, 20));

        //  Grave Itation  ----
        tabGraveItation_->addWidget(new LabeledBox(locales::getLocale(locales::LeftTeam),
			Vector2f(10, 30), 250, 80));
        tabGraveItation_->addWidget(new LabeledBox(locales::getLocale(locales::RightTeam),
			Vector2f(300, 30), 250, 80));
        RadioGroup* player1Group4 = new RadioGroup();
            player1Group4->addRadioButton(new RadioButton(settings::sPlayer1Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer1teamL,
			Vector2f(20,60), 80, true));
            player1Group4->addRadioButton(new RadioButton(settings::sPlayer1Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer1teamR,
			Vector2f(310,60), 80, true));
        tabGraveItation_->addWidget(player1Group4);
        RadioGroup* player2Group4 = new RadioGroup();
            player2Group4->addRadioButton(new RadioButton(settings::sPlayer2Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer2teamL,
			Vector2f(120,60), 80, true));
            player2Group4->addRadioButton(new RadioButton(settings::sPlayer2Name, locales::getLocale(locales::ttTeamPlayer),
			&settings::bPlayer2teamR,
			Vector2f(410,60), 80, true));
        tabGraveItation_->addWidget(player2Group4);
        tabGraveItation_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsLeft, 0, 20, 1,
			Vector2f(20,80), 230, 120, true));
        tabGraveItation_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsRight, 0, 20, 1,
			Vector2f(310,80), 230, 120, true));
        tabGraveItation_->addWidget(new LabeledBox(locales::getLocale(locales::GameOptions),
			Vector2f(10,120), 540, 80));
        tabGraveItation_->addWidget(new Slider(locales::Fraglimit, locales::ttPointLimitTeam,
			&settings::iPointLimitTDM, 1, 100, 1,
			Vector2f(20,150), 520, 270, true));

        //  Rally  (not done)  ----
        tabRally_->addWidget(new LabeledBox(locales::getLocale(locales::PlayerOptions),
			Vector2f(10, 30), 540, 80));
        tabRally_->addWidget(new Checkbox(settings::sPlayer1Name, locales::getLocale(locales::ttPlayersWho), &playerI_,
			Vector2f(20,60), 100));
        tabRally_->addWidget(new Checkbox(settings::sPlayer2Name, locales::getLocale(locales::ttPlayersWho), &playerII_,
			Vector2f(310,60), 100));
        tabRally_->addWidget(new Slider(locales::Bots, locales::ttBotCount,
			&settings::iBotsDeath, 0, 50, 1,
			Vector2f(20,80), 520, 270, true));
        tabRally_->addWidget(new LabeledBox(locales::getLocale(locales::GameOptions),
			Vector2f(10,120), 540, 100));
        
        tabRally_->addWidget(new Slider(locales::Fraglimit, locales::ttPointLimitTeam,
			&settings::iPointLimitDM, 1, 100, 1,
			Vector2f(20,150), 520, 270, true));
        tabRally_->addWidget(new Button(locales::getLocale(locales::WeaponOptions), "", &kWeaponOptions_,
			Vector2f(110,y2w), 120, 20));


        tabList->addTab(tabSpaceBall_);
        tabList->addTab(tabDeathMatch_);
        tabList->addTab(tabTeamDeathMatch_);
        tabList->addTab(tabCannonKeep_);
        tabList->addTab(tabGraveItation_);
        //tabList->addTab(tabRally_);

        instance_->addWidget(tabList);
    }
    return instance_;
}


void NewGameMenu::checkWidgets()
{
    if (kStart_)
    {   kStart_ = false;
        
        music::fadeOut();
        if (tabSpaceBall_->isActive())
        {
            menus::hideWindow();
            menus::hideWindow();
            settings::save();
            games::start(games::gSpaceBall);
        }
        else if (tabTeamDeathMatch_->isActive())
        {
            menus::hideWindow();
            menus::hideWindow();
            settings::save();
            games::start(games::gTeamDeathMatch);
        }
        else if (tabDeathMatch_->isActive())
        {
            menus::hideWindow();
            menus::hideWindow();
            settings::bPlayer1teamR = false;
            settings::bPlayer1teamL = false;
            settings::bPlayer2teamR = false;
            settings::bPlayer2teamL = false;
            if (playerI_)  settings::bPlayer1teamL  = true;
            if (playerII_) settings::bPlayer2teamL = true;
            settings::save();
            games::start(games::gDeathMatch);
        }
        else if (tabCannonKeep_->isActive())
        {
            menus::hideWindow();
            menus::hideWindow();
            settings::save();
            games::start(games::gCannonKeep);
        }
        else if (tabGraveItation_->isActive())
        {
            menus::hideWindow();
            menus::hideWindow();
            settings::save();
            settings::iPowerUpRate = 0;
            games::start(games::gGraveItation);
        }
        else if (tabRally_->isActive())
        {
            menus::hideWindow();
            menus::hideWindow();
            settings::bPlayer1teamR = false;
            settings::bPlayer1teamL = false;
            settings::bPlayer2teamR = false;
            settings::bPlayer2teamL = false;
            if (playerI_)  settings::bPlayer1teamL  = true;
            if (playerII_) settings::bPlayer2teamL = true;
            settings::save();
            games::start(games::gRally);
        }
    }
    else if (kInfo_)
    {   kInfo_ = false;
        if      (tabSpaceBall_->isActive())       menus::showWindow(InfoSB::get());
        else if (tabDeathMatch_->isActive())      menus::showWindow(InfoDM::get());
        else if (tabTeamDeathMatch_->isActive())  menus::showWindow(InfoTDM::get());
        else if (tabCannonKeep_->isActive())      menus::showWindow(InfoCK::get());
        else if (tabGraveItation_->isActive())    menus::showWindow(InfoGIP::get());
        else if (tabRally_->isActive())           menus::showWindow(InfoGIP::get());
    }
    else if (tSB_){   tSB_ = false;   if (settings::bShowInfoSB)   menus::showWindow(InfoSB::get());   }
    else if (tDM_){   tDM_ = false;   if (settings::bShowInfoDM)   menus::showWindow(InfoDM::get());   }
    else if (tTDM_){  tTDM_ = false;  if (settings::bShowInfoTDM)  menus::showWindow(InfoTDM::get());  }
    else if (tCK_){   tCK_ = false;   if (settings::bShowInfoCK)   menus::showWindow(InfoCK::get());   }
    else if (tGI_){   tGI_ = false;   if (settings::bShowInfoCK)   menus::showWindow(InfoGIP::get());  }
    else if (tRLY_){  tRLY_ = false;  if (settings::bShowInfoCK)   menus::showWindow(InfoGIP::get());  }

    else if (kWeaponOptions_)
    {   kWeaponOptions_ = false;
        menus::showWindow(WeaponOptions::get());
    }
    else if (kMapOptions_)
    {   kMapOptions_ = false;
        menus::showWindow(MapOptions::get());
    }
    else if (kGameOptions_)
    {   kGameOptions_ = false;
        menus::showWindow(GameOptions::get());
    }
    else if (kBallsOptions_)
    {   kBallsOptions_ = false;
        menus::showWindow(BallsOptions::get());
    }
    else if (kCancel_)
    {   kCancel_ = false;
        menus::hideWindow();
    }
}


void NewGameMenu::onShow()
{
    if (settings::bPlayer1teamL | settings::bPlayer1teamR)
        playerI_ = true;
    if (settings::bPlayer2teamL | settings::bPlayer2teamR)
        playerII_ = true;
}

void NewGameMenu::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
