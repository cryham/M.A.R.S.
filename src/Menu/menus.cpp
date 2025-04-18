#include "Menu/menus.hpp"

#include "Media/text.hpp"
#include "System/window.hpp"
#include "Menu/About.hpp"
#include "Menu/Connect.hpp"
#include "Menu/InfoCK.hpp"
#include "Menu/InfoSB.hpp"
#include "Menu/InfoDM.hpp"
#include "Menu/InfoTDM.hpp"
#include "Menu/InfoHide.hpp"
#include "Menu/MainMenu.hpp"
#include "Menu/PauseMenu.hpp"
#include "Menu/EndMenu.hpp"
#include "Menu/ExitConfirm.hpp"
#include "Interface/toolTip.hpp"
#include "defines.hpp"
#include "Games/games.hpp"

namespace menus 
{
    namespace
	{
        std::vector<UiWindow*> windowStack_;
        bool hidden_(false);
        UiElement* keyboardFixTarget_ = nullptr;
    }


    void showMain()
    {
        windowStack_.clear();
        showWindow(MainMenu::get());
    }

    void showPause()
    {
        if (!visible())
        {
            if (games::ended())
                showWindow(EndMenu::get());
            else
                showWindow(PauseMenu::get());
        }
    }

    void draw()
    {
        if (visible() && !hidden_)
        {
            for (auto& it : windowStack_)
                it->draw();

            Vector2f viewPort = window::getViewPort();
            text::drawScreenText(sf::String("M.A.R.S. ") +
                sf::String(VERSION_MAJOR) + "." + sf::String(VERSION_MINOR) + "." + sf::String(VERSION_PATCH),
                Vector2f(viewPort.x_-4.f, viewPort.y_-14.f) , 11.f, TEXT_ALIGN_RIGHT, Color3f(0.8, 0.8, 0.8));
            toolTip::draw();
        }
    }

    void mouseMoved(Vector2f const& position)
    {
        if (visible())
        {
            toolTip::mouseMoved(position);
            windowStack_.back()->mouseMoved(position);
            windowStack_.back()->checkWidgets();
        }
    }

    void mouseWheelMoved(Vector2f const& position, int delta)
    {
        if (visible())
            windowStack_.back()->mouseWheelMoved(position, delta);
    }

    void mouseLeft(bool down)
    {
        if (visible())
        {
            windowStack_.back()->mouseLeft(down);
            if (!down)
                windowStack_.back()->checkWidgets();
        }
    }

    void keyEvent(bool down, Key const& key)
    {
        if (down && key == settings::keyScreenShot && !menus::keyboardFixed())
            window::screenShot();
        else if (down && key == settings::keyAudioNext && !menus::keyboardFixed())
            music::next();
        else if (down && key == settings::keyAudioPrev && !menus::keyboardFixed())
            music::previous();

        if (visible())
        {
            if (keyboardFixTarget_)
            {   keyboardFixTarget_->keyEvent(down, key);
                windowStack_.back()->checkWidgets();
            }
            else if (down && key.navi_ == Key::nAbort)
            {
                if (hidden_)
                {   hidden_ = false;
                    window::showCursor(true);
                }
                else if (windowStack_.back() == MainMenu::get())
                    showWindow(ExitConfirm::get());
                else
                    hideWindow();
            }
            else if (down && key.navi_ == Key::nUp && !hidden_)
                windowStack_.back()->tabPrevious();
            else if (down && key.navi_ == Key::nDown && !hidden_)
                windowStack_.back()->tabNext();
            else if (!hidden_)
            {
                windowStack_.back()->keyEvent(down, key);
                windowStack_.back()->checkWidgets();
            }
        }
        else if (down && key.navi_ == Key::nAbort)
            showPause();
    }

    void textEntered(sf::Uint32 keyCode)
    {
        if (visible())
            windowStack_.back()->textEntered(keyCode);
    }

    void showWindow(UiWindow* toBeShown)
    {
        if (!toBeShown)
            return;
        window::showCursor(true);

        toBeShown->onShow();
        toBeShown->setTopMost(true);
        if (visible())
            windowStack_.back()->setTopMost(false);
        windowStack_.push_back(toBeShown);
    }

    void hideWindow()
    {
        windowStack_.pop_back();
        if (!visible())
            window::showCursor(false);
        else
            windowStack_.back()->setTopMost(true);
    }

    void hideMenu()
    {
        window::showCursor(false);
        hidden_ = true;
    }

    void clearFocus()
    {
        if (visible())
            windowStack_.back()->clearFocus();
    }

    void fixKeyboardOn(UiElement* target)
    {
        keyboardFixTarget_ = target;
    }

    void unFixKeyboard()
    {
        keyboardFixTarget_ = nullptr;
    }

    bool keyboardFixed()
    {
        return keyboardFixTarget_;
    }

    void reload()
    {
        About::reset();
        Connect::reset();
        InfoCK::reset();
        InfoDM::reset();
        InfoHide::reset();
        InfoSB::reset();
        InfoTDM::reset();
    }

    bool visible()
    {
        return !windowStack_.empty();
    }
}
