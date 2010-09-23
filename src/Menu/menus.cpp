/*menus.cpp

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.*/

# include "Menu/menus.hpp"

# include "Hud/hud.hpp"
# include "System/window.hpp"
# include "Menu/MainMenu.hpp"
# include "Menu/PauseMenu.hpp"
# include "Menu/ExitConfirm.hpp"

namespace menus {

    namespace {
        std::vector<UiWindow*> windowStack_;
    }

    void showMain() {
        if (!visible())
            showWindow(MainMenu::get());
    }

    void showPause() {
        if (!visible())
            showWindow(PauseMenu::get());
    }

    void draw() {
        if (visible()) {
            window::setPixelView();
            for (std::vector<UiWindow*>::iterator it = windowStack_.begin(); it != windowStack_.end(); ++it)
                (*it)->draw();
            Vector2f viewPort = window::getViewPort();
            hud::drawScreenText("M.A.R.S. 0.3.2 - " + std::string(__DATE__), Vector2f(viewPort.x_-4.f, viewPort.y_-14.f) , font::HandelGotDLig, 11.f, TEXT_ALIGN_RIGHT, Color3f(0.8, 0.8, 0.8));
            window::setSpaceView();
        }
    }

    void mouseMoved(Vector2f const& position) {
        if (visible()) {
            windowStack_.back()->mouseMoved(position);
            windowStack_.back()->checkWidgets();
        }
    }

    void mouseLeft(bool down) {
        if (visible()) {
            windowStack_.back()->mouseLeft(down);
            if (!down) windowStack_.back()->checkWidgets();
        }
    }

    void buttonPressed(sf::Key::Code keyCode) {
        if (visible()) {
            if (keyCode == sf::Key::Escape) {
                if (windowStack_.back() == MainMenu::get())
                    showWindow(ExitConfirm::get());
                else
                    hideWindow();
            }
            else
                windowStack_.back()->buttonPressed(keyCode);
        }
        else if (keyCode == sf::Key::Escape)
            showPause();
    }

    void textEntered(int keyCode) {
        if (visible())
            windowStack_.back()->textEntered(keyCode);
    }

    void showWindow(UiWindow* toBeShown) {
        window::showCursor(true);
        toBeShown->onShow();
        toBeShown->setActive(true);
        if (visible()) windowStack_.back()->setActive(false);
        windowStack_.push_back(toBeShown);
    }

    void hideWindow() {
        windowStack_.pop_back();
        if (!visible()) window::showCursor(false);
        else windowStack_.back()->setActive(true);
    }

    bool visible() {
        return !windowStack_.empty();
    }
}
