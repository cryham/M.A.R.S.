/* TabList.cpp

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

# include "Interface/TabList.hpp"

# include "System/settings.hpp"
# include "System/window.hpp"

# include <SFML/OpenGL.hpp>

TabList::TabList (Vector2f const& topLeft, int width, int height):
    UiElement(topLeft, width, height),
    lastTabEnd_(0) {}

TabList::~TabList() {
    for (std::vector<Tab*>::iterator i=tabs_.begin(); i != tabs_.end(); ++i)
        delete *i;
}

void TabList::mouseMoved(Vector2f const& position) {
    for (std::vector<Tab*>::iterator i=tabs_.begin(); i != tabs_.end(); ++i)
        (*i)->mouseMoved(position);
}

void TabList::mouseLeft(bool down) {
    for (std::vector<Tab*>::iterator i=tabs_.begin(); i != tabs_.end(); ++i)
        (*i)->mouseLeft(down);
}

void TabList::buttonPressed(sf::Key::Code keyCode) {
    for (std::vector<Tab*>::iterator i=tabs_.begin(); i != tabs_.end(); ++i)
        (*i)->buttonPressed(keyCode);
}

void TabList::textEntered(int keyCode) {
    for (std::vector<Tab*>::iterator i=tabs_.begin(); i != tabs_.end(); ++i)
        (*i)->textEntered(keyCode);
}

void TabList::draw () const {
    Vector2f origin = parent_->getTopLeft() + topLeft_;


    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    /*glBegin(GL_QUADS);
        glColor4f(1,0.5,0.8,0.0);
        glVertex2f(origin.x_,origin.y_+height_*0.2);
        glVertex2f(origin.x_+width_,origin.y_+height_*0.2);
        glColor4f(1,0.5,0.8,0.4);
        glVertex2f(origin.x_+width_,origin.y_+20);
        glVertex2f(origin.x_,origin.y_+20);
    glEnd();*/

    glLineWidth(2.f);
    glBegin(GL_LINES);
        glColor4f(1.f, 0.5f, 0.8f, 1.0f);
        glVertex2f(origin.x_,origin.y_+20);
        glColor4f(1.f, 0.5f, 0.8f, 0.0f);
        glVertex2f(origin.x_,origin.y_+height_);

        glColor4f(1.f, 0.5f, 0.8f, 1.0f);
        glVertex2f(origin.x_+lastTabEnd_,origin.y_+20);
        glColor4f(1.f, 0.5f, 0.8f, 0.0f);
        glVertex2f(origin.x_+width_,origin.y_+20);
    glEnd();



    for (std::vector<Tab*>::const_iterator i=tabs_.begin(); i != tabs_.end(); ++i)
        (*i)->draw();
}

void TabList::addTab(Tab* toBeAdded) {
    toBeAdded->setParent(this);

    if (tabs_.size() == 0)
        toBeAdded->active_ = true;

    toBeAdded->topLeft_ = Vector2f(lastTabEnd_, 0.f);

    toBeAdded->label_ = new Label(toBeAdded->name_, TEXT_ALIGN_CENTER, Vector2f(lastTabEnd_+toBeAdded->width_/2, -6));
    toBeAdded->label_->setParent(toBeAdded);

    tabs_.push_back(toBeAdded);

    lastTabEnd_ += toBeAdded->width_;
}

void TabList::deactivateAll() {
    for (std::vector<Tab*>::iterator i=tabs_.begin(); i != tabs_.end(); ++i)
        (*i)->active_ = false;
}

void TabList::clearTabs() {
    for (std::vector<Tab*>::iterator i=tabs_.begin(); i != tabs_.end(); ++i)
        delete *i;
    tabs_.clear();
}

