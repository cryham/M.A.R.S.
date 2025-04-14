/* OptionsMenu.cpp

Copyright (c) 2025 Crystal Hammer
Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "Menu/OptionsMenu.hpp"

#include "Media/text.hpp"
#include "Interface/UiElement.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/Slider.hpp"
#include "Interface/Checkbox.hpp"
#include "Interface/Tab.hpp"
#include "Interface/TabList.hpp"
#include "Interface/KeyEdit.hpp"
#include "Interface/TextEdit.hpp"
#include "Interface/ShipPreview.hpp"
#include "Interface/Line.hpp"
#include "Interface/RadioGroup.hpp"
#include "Interface/RadioButton.hpp"
#include "Interface/ComboBox.hpp"
#include "Interface/LanguageButton.hpp"
#include "Interface/ColorPicker.hpp"
#include "Interface/LabeledBox.hpp"
#include "System/Color3f.hpp"
#include "System/window.hpp"
#include "System/settings.hpp"
#include "Menu/menus.hpp"
#include "System/generateName.hpp"
#include "Media/music.hpp"
#include "Particles/Star.hpp"
#include "Media/sound.hpp"
#include "Locales/locales.hpp"
#include "Menu/ChooseLanguage.hpp"
#include "Menu/ShaderError.hpp"
#include "Menu/About.hpp"
#include "Menu/Connect.hpp"
#include "Menu/InfoCK.hpp"
#include "Menu/InfoSB.hpp"
#include "Menu/InfoDM.hpp"
#include "Menu/InfoTDM.hpp"
#include "Menu/InfoHide.hpp"
#include "Shaders/postFX.hpp"
#include "defines.hpp"

#include <SFML/Window.hpp>
#include <sstream>


UiWindow* OptionsMenu::instance_(NULL);
bool OptionsMenu::kOk_(false);
bool OptionsMenu::fullscreen_(false);
bool OptionsMenu::vsync_(false);
bool OptionsMenu::shaders_(false);
int OptionsMenu::starfield_(0);
sf::String OptionsMenu::resolution_("");
sf::String OptionsMenu::colorDepth_("");
sf::String OptionsMenu::format_("");
int  OptionsMenu::soundVolume_(0);
int  OptionsMenu::musicVolume_(0);
int  OptionsMenu::announcerVolume_(0);
int  OptionsMenu::UIscale_(100);


UiWindow* OptionsMenu::get()
{
    if (instance_ == NULL)
    {
        instance_ = new OptionsMenu(700, 390);

        instance_->addWidget(new Button(locales::getLocale(locales::Ok), "", &kOk_,
            Vector2f(500,360), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::Options), TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));

        TabList* tabList  = new TabList(Vector2f(10,55), 580, 270);
        Tab* tabInterface = new Tab(locales::getLocale(locales::Interface), 90);
        Tab* tabGraphics  = new Tab(locales::getLocale(locales::Display), 80);
        Tab* tabGameplay  = new Tab(locales::getLocale(locales::Gameplay), 90);
        Tab* tabView      = new Tab(locales::getLocale(locales::View), 80);
        Tab* tabAudio     = new Tab(locales::getLocale(locales::Audio), 80);
        
        Tab* tabShips     = new Tab(locales::getLocale(locales::ShipName), 80);  //ShipSettings
        Tab* tabPlayer1   = new Tab(settings::sPlayer1Name, 100);
        Tab* tabPlayer2   = new Tab(settings::sPlayer2Name, 100);


        //  Interface GUI  ----
        int y = 30, yadd = 20, xTxt = 240;
        tabInterface->addWidget(new LabeledBox(locales::getLocale(locales::GeneralOptions),
            Vector2f(10, y), 560, 110));  y += yadd*3/2;
        tabInterface->addWidget(new LanguageButton(locales::getLocale(locales::Language),
            Vector2f(20, y), 540, xTxt));  y += yadd;

        tabInterface->addWidget(new Slider(locales::Scale, locales::ttScale,
            &UIscale_, 80, 400, 10,
            Vector2f(20,y), 540, xTxt, true));  y += yadd*3/2;
        
        tabInterface->addWidget(new Checkbox(locales::ShowToolTips, locales::ttShowToolTips,
            &settings::bShowToolTips,
            Vector2f(20,y), 140));  y += yadd;
        tabInterface->addWidget(new Checkbox(locales::NoConfirmations, locales::ttNoConfirmations,
            &settings::bNoConfirmations,
            Vector2f(20,y), 140));  y += yadd;
        tabInterface->addWidget(new Checkbox(locales::LogoSigns, locales::ttNoConfirmations,
            &settings::bLogoSigns,
            Vector2f(20,y), 140));  y += yadd*3/2;

        std::vector<sf::String> fileFormats;
            fileFormats.push_back("BITMAP (*.bmp)");
            fileFormats.push_back("GIF (*.gif)");
            fileFormats.push_back("JPEG (*.jpg)");
            fileFormats.push_back("PNG(*.png)");
            fileFormats.push_back("TARGA (*.tga)");
        tabInterface->addWidget(new ComboBox(locales::ScreenShotFormat, locales::ttScreenShotFormat,
            &format_, fileFormats,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabInterface->addWidget(new KeyEdit(locales::ScreenShotKey, locales::ttScreenShotKey,
            &settings::keyScreenShot,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabInterface->addWidget(new KeyEdit(locales::StatisticsKey, locales::ttStatisticsKey,
            &settings::keyStatistics,
            Vector2f(20,y), 540, xTxt));  y += yadd*2;


        //  Graphics  ----
        y = 30;
        std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
        std::vector<sf::String> resolutions;
        std::vector<sf::String> colorDepths;
        for (auto& it : modes)
        {
            if (it.width >= 800 && it.bitsPerPixel >= 8)
            {
                std::stringstream res, depth;
                res << it.width << " x " << it.height;
                depth << it.bitsPerPixel;
                sf::String resString(res.str()), depthString(depth.str());

                bool newDepth(true), newRes(true);
                for (auto& it : resolutions)
                    if (it == resString)
                        newRes = false;
                for (auto& it : colorDepths)
                    if (it == depthString) newDepth = false;
                
                if (newRes)
                    resolutions.push_back(res.str());
                if (newDepth)
                    colorDepths.push_back(depth.str());
            }
        }
        std::vector<sf::String> off;
        off.push_back(locales::getLocale(locales::SlowMoOff));

        //  screen
        tabGraphics->addWidget(new LabeledBox(locales::getLocale(locales::WindowSettings),
            Vector2f(10, y), 560, 110));  y += yadd*3/2;
        tabGraphics->addWidget(new ComboBox(locales::Resolution, locales::ttResolution,
            &resolution_, resolutions,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabGraphics->addWidget(new Checkbox(locales::Fullscreen, locales::ttFullscreen,
            &fullscreen_,
            Vector2f(20,y), 150));  y += yadd;
        tabGraphics->addWidget(new Checkbox(locales::VerticalSynchronisation, locales::ttVerticalSynchronisation,
            &vsync_,
            Vector2f(20,y), 150));  y += yadd;
        tabGraphics->addWidget(new Slider(locales::getLocale(locales::AntiAliasing), "",
            &settings::iAntiAliasing, 0, 16, 1,
            Vector2f(20,y), 540, xTxt, true, off));  y += yadd;

        tabGraphics->addWidget(new Checkbox(locales::Shaders, locales::ttShaders,
            &shaders_,
            Vector2f(20,y), 150));
        tabGraphics->addWidget(new Checkbox(locales::getLocale(locales::Flashes), "",
            &settings::bFlashes,
            Vector2f(xTxt,y), 150));  y += yadd*2;

        tabGraphics->addWidget(new LabeledBox(locales::getLocale(locales::GameSettings),
            Vector2f(10,y), 560, 90));  y += yadd*3/2;
        tabGraphics->addWidget(new Checkbox(locales::StarsHigh, locales::ttStarsHigh,
            &settings::bStarsHigh,
            Vector2f(20,y), 150));  y += yadd;
        tabGraphics->addWidget(new Slider(locales::StarField, locales::ttStarField,
            &starfield_, 0, 20000, 1000,
            Vector2f(20,y), 540, xTxt, true, off));  y += yadd*3/2;
        
        //  particles
        tabGraphics->addWidget(new Slider(locales::ParticleCountSlider, locales::ttParticleCountSlider,
            &settings::iParticleCount, 1, 300, 15,
            Vector2f(20,y), 540, xTxt, true));  y += yadd;
        tabGraphics->addWidget(new Slider(locales::ParticleLifetime, locales::ttParticleLifetime,
            &settings::iParticleLifeTime, 1, 300, 15,
            Vector2f(20,y), 540, xTxt, true));  y += yadd;


        //  Gameplay  ----
        y = 30.f;
        tabGameplay->addWidget(new LabeledBox(locales::getLocale(locales::SpecialEffects),
            Vector2f(10,y), 560, 90));  y += yadd*3/2;
        tabGameplay->addWidget(new Slider(locales::GameSpeed, locales::ttGameSpeed,
            &settings::iGameSpeed, 50, 200, 5,
            Vector2f(20,y), 540, xTxt, true));  y += yadd*3/2;
        
        tabGameplay->addWidget(new Slider(locales::getLocale(locales::CountDown), "",
            &settings::iCountDown, 0, 6, 1,
            Vector2f(20,y), 540, xTxt, true, off));  y += yadd;
        tabGameplay->addWidget(new Slider(locales::SlowMoKickIn, locales::ttSlowMoKickIn,
            &settings::iSlowMoKickIn, 0, 10, 1,
            Vector2f(20,y), 540, xTxt, true, off));  y += yadd;

        //  View debug  ----
        y = 30.f;
        tabView->addWidget(new LabeledBox(locales::getLocale(locales::GameInformation),
            Vector2f(10, y), 560, 90));  y += yadd*3/2;
        tabView->addWidget(new Checkbox(locales::FramesPerSecond, locales::ttFramesPerSecond,
            &settings::bShowFPS,
            Vector2f(20,y), 140));  y += yadd;
        tabView->addWidget(new Checkbox(locales::ParticleCount, locales::ttParticleCount,
            &settings::bShowParticleCount,
            Vector2f(20,y), 140));  y += yadd*2;

        tabView->addWidget(new LabeledBox(locales::getLocale(locales::DebuggingInformation),
            Vector2f(10,y), 560, 90));  y += yadd*3/2;
        tabView->addWidget(new Checkbox(locales::AIJobs, locales::ttBotsOrientation, &settings::bDrawBotJobs,
            Vector2f(20,y), 140));  y += yadd;
        tabView->addWidget(new Checkbox(locales::Zones, locales::ttZones, &settings::bDrawZones,
            Vector2f(20,y), 140));  y += yadd;
        tabView->addWidget(new Checkbox(locales::AIPaths, locales::ttAIPaths, &settings::bDrawAIPath,
            Vector2f(20,y), 140));  y += yadd;


        //  Audio  ----
        y = 30.f;
        tabAudio->addWidget(new LabeledBox(locales::getLocale(locales::VolumeSettings),
            Vector2f(10,y), 560, 90));  y += yadd*3/2;
        tabAudio->addWidget(new Slider(locales::MusicVolume, locales::ttMusicVolume,
            &musicVolume_, 0, 100, 5,
            Vector2f(20,y), 540, xTxt, true, off));  y += yadd;
        tabAudio->addWidget(new Slider(locales::SoundVolume, locales::ttSoundVolume,
            &soundVolume_, 0, 100, 5,
            Vector2f(20,y), 540, xTxt, true, off));  y += yadd;
        tabAudio->addWidget(new Slider(locales::AnnouncerVolume, locales::ttAnnouncerVolume,
            &announcerVolume_, 0, 100, 5,
            Vector2f(20,y), 540, xTxt, true, off));  y += yadd*2;
        
        tabAudio->addWidget(new LabeledBox(locales::getLocale(locales::PlaybackSettings),
            Vector2f(10,y), 560, 60));  y += yadd*3/2;
        tabAudio->addWidget(new Checkbox(locales::AudioRandom, locales::ttAudioRandom,
            &settings::bAudioRandom,
            Vector2f(20,y), 150));  y += yadd;
        tabAudio->addWidget(new KeyEdit(locales::AudioNextKey, locales::ttAudioNextKey,
            &settings::keyAudioNext,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabAudio->addWidget(new KeyEdit(locales::AudioPreviousKey, locales::ttAudioPreviousKey,
            &settings::keyAudioPrev,
            Vector2f(20,y), 540, xTxt));  y += yadd;


        //  Ships  ----
        y = 30.f;
        tabShips->addWidget(new LabeledBox(settings::sPlayer1Name,
            Vector2f(10,y), 560, 90));  y += yadd*3/2;
        tabShips->addWidget(new ShipPreview(
            &settings::clr1Player, &settings::clr1Team, &settings::iPlayer1Ship,
            Vector2f(510,y)));  //y += yadd;
        tabShips->addWidget(new Slider(locales::getLocale(locales::ShipName), "",
            &settings::iPlayer1Ship, 0, SHIP_GRAPHICS_COUNT, 1,
            Vector2f(20,y), 410, xTxt, true, generateName::shipNames()));  y += yadd;
        tabShips->addWidget(new ColorPicker(locales::getLocale(locales::PlayerColor), &settings::clr1Player,
            Vector2f(20,y), 410, xTxt));  y += yadd;
        tabShips->addWidget(new ColorPicker(locales::getLocale(locales::TeamColor), &settings::clr1Team,
            Vector2f(20,y), 410, xTxt));  y += yadd;

        tabShips->addWidget(new LabeledBox(settings::sPlayer2Name,
            Vector2f(10, y), 560, 90));  y += yadd*3/2;
        tabShips->addWidget(new ShipPreview(
            &settings::clr2Player, &settings::clr2Team, &settings::iPlayer2Ship,
            Vector2f(510,y)));  //y += yadd;
        tabShips->addWidget(new Slider(locales::getLocale(locales::ShipName), "",
            &settings::iPlayer2Ship, 0, SHIP_GRAPHICS_COUNT, 1,
            Vector2f(20,y), 410, xTxt, true, generateName::shipNames()));  y += yadd;
        tabShips->addWidget(new ColorPicker(locales::getLocale(locales::PlayerColor), &settings::clr2Player,
            Vector2f(20,y), 410, xTxt));  y += yadd;
        tabShips->addWidget(new ColorPicker(locales::getLocale(locales::TeamColor), &settings::clr2Team,
            Vector2f(20,y), 410, xTxt));  y += yadd*3/2;

        tabShips->addWidget(new LabeledBox(locales::getLocale(locales::GameOptions),
            Vector2f(10, y), 560, 90));  y += yadd*3/2;
        tabShips->addWidget(new Slider(locales::getLocale(locales::ShipTurnSpeed), "",
           &settings::iShipTurnSpeed, 1, 60, 1,
           Vector2f(20,y), 540, 240, true));  y += yadd;
        tabShips->addWidget(new Slider(locales::getLocale(locales::GlowAlpha), "",
           &settings::iGlowAlpha, 0, 150, 1,
           Vector2f(20,y), 540, 240, true));  y += yadd*3/2;


        //  Player I keys  ----
        y = 30.f;
        tabPlayer1->addWidget(new TextEdit(locales::getLocale(locales::Name), settings::sPlayer1Name, "PlayerI",
            Vector2f(20,y), 540, xTxt, TEXT_EDIT, 12));  y += yadd*3/2;

        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::Accelerate),     "", &settings::key1up,
            Vector2f(20,y), 540, xTxt, Color3f(0.5f, 0.76f, 1.f)));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::AccelerateBack), "", &settings::key1down,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::Boost),          "", &settings::key1boost,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        
        tabPlayer1->addWidget(new Checkbox(locales::MouseRotationAim, locales::ttMouseRotationAim, &settings::bPlayer1mouseAim,
            Vector2f(20,y), 140));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::TurnLeft),  "", &settings::key1left,
            Vector2f(20,y), 540, xTxt, Color3f(1.f, 1.f, 0.8f)));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::TurnRight), "", &settings::key1right,
            Vector2f(20,y), 540, xTxt));  y += yadd*3/2;

        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::Fire),        "", &settings::key1fire,
            Vector2f(20,y), 540, xTxt, Color3f(1.f, 0.8f, 0.6f)));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::SpecialKey),  "", &settings::key1SpecialKey,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::PrevWeapon),  "", &settings::key1prev,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::NextWeapon),  "", &settings::key1next,
            Vector2f(20,y), 540, xTxt));  y += yadd;

        //  Player II keys  ----
        y = 30.f;
        tabPlayer2->addWidget(new TextEdit(locales::getLocale(locales::Name), settings::sPlayer2Name, "PlayerII",
            Vector2f(20,y), 540, xTxt, TEXT_EDIT, 12));  y += yadd*3/2;

        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::Accelerate),     "", &settings::key2up,
            Vector2f(20,y), 540, xTxt, Color3f(0.5f, 0.76f, 1.f)));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::AccelerateBack), "", &settings::key2down,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::Boost),          "", &settings::key2boost,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        
        tabPlayer2->addWidget(new Checkbox(locales::MouseRotationAim, locales::ttMouseRotationAim, &settings::bPlayer2mouseAim,
            Vector2f(20,y), 140));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::TurnLeft),  "", &settings::key2left,
            Vector2f(20,y), 540, xTxt, Color3f(1.f, 1.f, 0.8f)));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::TurnRight), "", &settings::key2right,
            Vector2f(20,y), 540, xTxt));  y += yadd*3/2;

        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::Fire),        "", &settings::key2fire,
            Vector2f(20,y), 540, xTxt, Color3f(1.f, 0.8f, 0.6f)));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::SpecialKey),  "", &settings::key2SpecialKey,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::PrevWeapon),  "", &settings::key2prev,
            Vector2f(20,y), 540, xTxt));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::NextWeapon),  "", &settings::key2next,
            Vector2f(20,y), 540, xTxt));  y += yadd;


        tabList->addTab(tabInterface);
        tabList->addTab(tabGraphics);
        tabList->addTab(tabAudio);
        tabList->addTab(tabGameplay);
        tabList->addTab(tabView);

        tabList->addTab(tabShips);
        tabList->addTab(tabPlayer2);
        tabList->addTab(tabPlayer1);
        instance_->addWidget(tabList);
    }
    return instance_;
}


void OptionsMenu::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;

        int resX, resY, depth;
        std::stringstream sstr1(resolution_);
        sstr1 >> resX;
        char x; sstr1 >> x;
        sstr1 >> resY;

        std::stringstream sstr2(colorDepth_);
        sstr2 >> depth;

        if (resX != settings::iResX || resY != settings::iResY ||
            depth != settings::iColorDepth ||
            fullscreen_ != settings::bFullScreen || vsync_ != settings::bVSync ||
            shaders_ != settings::bShaders)
        {
            settings::iResX = resX;
            settings::iResY = resY;
            settings::iColorDepth = depth;
            settings::bFullScreen = fullscreen_;
            settings::bVSync = vsync_;
            settings::bShaders = shaders_;
            window::create();
        }

        if      (format_ == "BITMAP (*.bmp)") settings::sScreenShotFormat = "bmp";
        else if (format_ == "GIF (*.gif)")    settings::sScreenShotFormat = "gif";
        else if (format_ == "TARGA (*.tga)")  settings::sScreenShotFormat = "tga";
        else if (format_ == "PNG(*.png)")     settings::sScreenShotFormat = "png";
        else if (format_ == "JPEG (*.jpg)")   settings::sScreenShotFormat = "jpg";

        if (starfield_ != settings::iStarField)
        {
            settings::iStarField = starfield_;
            if (settings::iStarField > 0)
                Star::init();
            else
                Star::clear();
        }

        locales::load();
        menus::reload();

        settings::save();
        menus::hideWindow();
    }
    if (shaders_ != settings::bShaders)
    {
        if (shaders_ && !postFX::supported())
        {
            shaders_ = false;
            settings::bShaders = false;
            menus::showWindow(ShaderError::get());
        }
    }
    if (soundVolume_ != settings::iSoundVolume)
        settings::iSoundVolume = soundVolume_;

    if (musicVolume_ != settings::iMusicVolume)
    {
        settings::iMusicVolume = musicVolume_;
        music::setGlobalVolume();
    }
    if (announcerVolume_ != settings::iAnnouncerVolume)
        settings::iAnnouncerVolume = announcerVolume_;

    if (UIscale_ != scale_ * 100.f)
    {   scale_ = UIscale_ / 100.f;

        settings::save();
        menus::hideWindow();
        // menus::reload();
        OptionsMenu::reset();
        menus::showWindow(OptionsMenu::get());
    }
}


void OptionsMenu::onShow()
{
    fullscreen_      = settings::bFullScreen;
    vsync_           = settings::bVSync;
    shaders_         = settings::bShaders;
    soundVolume_     = settings::iSoundVolume;
    musicVolume_     = settings::iMusicVolume;
    announcerVolume_ = settings::iAnnouncerVolume;
    starfield_       = settings::iStarField;
    UIscale_         = scale_ * 100.f;

    if      (settings::sScreenShotFormat == "bmp")  format_ = "BITMAP (*.bmp)";
    else if (settings::sScreenShotFormat == "gif")  format_ = "GIF (*.gif)";
    else if (settings::sScreenShotFormat == "tga")  format_ = "TARGA (*.tga)";
    else if (settings::sScreenShotFormat == "png")  format_ = "PNG(*.png)";
    else if (settings::sScreenShotFormat == "jpg")  format_ = "JPEG (*.jpg)";

    sf::VideoMode mode(settings::iResX, settings::iResY);
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    if (modes.size() > 0 && !mode.isValid())
    {
        mode = sf::VideoMode::getFullscreenModes().front();
        settings::iResX = mode.width;
        settings::iResY = mode.height;
    }

    std::stringstream sstr1;
    sstr1 << settings::iResX << " x " << settings::iResY;
    resolution_ = sstr1.str();

    std::stringstream sstr2;
    sstr2 << settings::iColorDepth;
    colorDepth_ = sstr2.str();
}

void OptionsMenu::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}
