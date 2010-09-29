/* InfoCK.cpp

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

# include "Menu/InfoCK.hpp"

# include "Interface/UiWindow.hpp"
# include "Interface/Button.hpp"
# include "Menu/menus.hpp"
# include "Interface/TextBox.hpp"
# include "Interface/Checkbox.hpp"
# include "Interface/Line.hpp"
# include "Media/text.hpp"
# include "System/settings.hpp"

UiWindow* InfoCK::instance_(NULL);
bool InfoCK::kClose_(false);

UiWindow* InfoCK::get() {
    if (instance_ == NULL) {
        instance_ = new InfoCK(320, 430);
        instance_->addWidget(new Button("Close", &kClose_, Vector2f(240,400), 70, 20));
        instance_->addWidget(new Label("CannonKeep", TEXT_ALIGN_LEFT, Vector2f(10,10), 20.f));
        instance_->addWidget(new Label("Rules and Infos", TEXT_ALIGN_RIGHT, Vector2f(310,18), 12.f));
        instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));
        instance_->addWidget(new Label("Pick up the remote and keep it as long as possible!", TEXT_ALIGN_LEFT, Vector2f(10,50), 12.f, Color3f(1.f, 0.7f, 0.9f)));
        instance_->addWidget(new TextBox("As if the GREAT WAR was not enough, your planetary system is threatened by a new source of incredible evilness: A giant ship of unknown invaders is levitating over your galaxy, aiming on the home planets with a monolithic weapon of mass destruction. \nAs a sign of cynicism, the attackers dropped a remote control to adjust this provenance of death and fear. \nReach it first to turn your enemy's home planet into a place of desolation! \nBe the CANNONKEEPer. \n \nUse the keys you configured in options menu for controlling your ship. \nTo change your weapon, land on your planet, press \nFIRE and then navigate through the weapons by pressing LEFT or RIGHT. \nUse TAB to show statistics about the current game.", Vector2f(10, 80), 300, 300));
        instance_->addWidget(new Checkbox("Show this info again.", &settings::C_showInfoCK, Vector2f(10,400), 170));
    }
    return instance_;
}

void InfoCK::checkWidgets() {
    if (kClose_) {
        kClose_ = false;
        menus::hideWindow();
        settings::save();
    }
}






