#include "Interface/TabList.hpp"

#include "System/settings.hpp"
#include "System/window.hpp"
#include "Media/text.hpp"
#include "Media/sound.hpp"
#include "Menu/menus.hpp"
#include "Locales/locales.hpp"

#include <SFML/OpenGL.hpp>


TabList::TabList (Vector2f const& topLeft, int width, int height):
    UiElement(topLeft * 1.f/scale_,  width * 1.f/scale_, height),
    lastTabEnd_(0)
{   }

TabList::~TabList()
{
    for (auto& it : tabs_)
        delete it;
}

void TabList::mouseMoved(Vector2f const& position)
{
    for (auto& it : tabs_)
        it->mouseMoved(position);
}

void TabList::mouseWheelMoved(Vector2f const& position, int delta)
{
    for (auto& it : tabs_)
        it->mouseWheelMoved(position, delta);
}

void TabList::mouseLeft(bool down)
{
    for (auto& it : tabs_)
        it->mouseLeft(down);
}

void TabList::keyEvent(bool down, Key const& key)
{
    if (focusedTab_)
    {
        if (focusedTab_->isFocused())
            focusedTab_->keyEvent(down, key);
        else
        {
            if (down && ((key.navi_ == Key::nLeft && locales::getCurrentLocale().LTR_) ||
                         (key.navi_ == Key::nRight && !locales::getCurrentLocale().LTR_)))
            {
                int i(0);
                while ( tabs_[i] != focusedTab_) i = (i-1 + tabs_.size())%tabs_.size();
                i = (i-1 + tabs_.size())%tabs_.size();
                while (!tabs_[i]->isTabable())   i = (i-1 + tabs_.size())%tabs_.size();

                focusedTab_->active_=false;
                focusedTab_ = tabs_[i];
                focusedTab_->active_=true;
            }
            if (down && ((key.navi_ == Key::nRight && locales::getCurrentLocale().LTR_) ||
                         (key.navi_ == Key::nLeft && !locales::getCurrentLocale().LTR_)))
            {
                int i(0);
                while ( tabs_[i] != focusedTab_) i = (i+1)%tabs_.size();
                i = (i+1)%tabs_.size();
                while (!tabs_[i]->isTabable())   i = (i+1)%tabs_.size();

                focusedTab_->active_=false;
                focusedTab_ = tabs_[i];
                focusedTab_->active_=true;
            }
        }
    }
}

bool TabList::tabNext()
{
    if (focusedTab_)
    {
        if (focusedTab_->isFocused())
        {
            return focusedTab_->tabNext();
        }
        else
        {
            focusedTab_->setFocus(focusedTab_, false);
            focusedTab_->tabNext();
            return false;
        }
    }
    return true;
}

bool TabList::tabPrevious()
{
    if (focusedTab_)
    {
        if (focusedTab_->isFocused())
        {
            if (focusedTab_->tabPrevious())
            {
                menus::clearFocus();
                //
                // THIS ONE IS HACKY! the false below is a workaround to make tabLists tabable from below...
                // it's therefore impossible to place tabLists inside of other Tablists...
                //
                setFocus(this, false);
            }
            return false;
        }else
            return true;
    }
    return true;
}

void TabList::textEntered(sf::Uint32 keyCode)
{
    if (focusedTab_)
        focusedTab_->textEntered(keyCode);
}

void TabList::draw () const
{
    Vector2f origin = getTopLeft();

    int mirror(locales::getCurrentLocale().LTR_ ? 1 : -1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    /*glLineWidth(2.f);
    glBegin(GL_LINES);
        if (isTopMost())  setColor4f(0.5f, 0.8f, 1.0f, 1.0f);
        else              setColor4f(0.4f, 0.4f, 0.4f, 1.0f);
        glVertex2f(origin.x_,origin.y_+20);
        if (isTopMost())  setColor4f(0.5f, 0.8f, 1.0f, 0.0f);
        else              setColor4f(0.4f, 0.4f, 0.4f, 0.0f);
        glVertex2f(origin.x_,origin.y_+height_);

        if (isTopMost())  setColor4f(0.5f, 0.8f, 1.0f, 1.0f);
        else              setColor4f(0.4f, 0.4f, 0.4f, 1.0f);
        glVertex2f(origin.x_+lastTabEnd_*mirror,origin.y_+20);
        if (isTopMost())  setColor4f(0.5f, 0.8f, 1.0f, 0.0f);
        else              setColor4f(0.4f, 0.4f, 0.4f, 0.0f);
        glVertex2f(origin.x_+width(),origin.y_+20);
    glEnd();*/

    for (const auto& it : tabs_)
        it->draw();
}

void TabList::setFocus(UiElement* toBeFocused, bool isPrevious)
{
    UiElement::setFocus(this, isPrevious);
    Tab* toFocus = dynamic_cast<Tab*>(toBeFocused);
    if (toFocus)
        focusedTab_ = toFocus;
    else
    if (toBeFocused == this && isPrevious && focusedTab_ && !focusedTab_->isFocused())
        focusedTab_->tabPrevious();
}

void TabList::clearFocus()
{
    UiElement::clearFocus();
    for (auto& it : tabs_)
        it->clearFocus();
}

void TabList::addTab(Tab* toBeAdded)
{
    toBeAdded->setParent(this);

    if (tabs_.size() == 0)
        toBeAdded->active_ = true;

    toBeAdded->topLeft_ = Vector2f(lastTabEnd_, 0.f);
    toBeAdded->width_ *= scale_;

    toBeAdded->label_ = new Label(toBeAdded->name_, TEXT_ALIGN_CENTER,
        Vector2f(lastTabEnd_+toBeAdded->width_/2, -6) * 1.f/scale_,
        12.f, getColor3f(0.85f, 0.95f, 1.0f), false);
    toBeAdded->label_->setParent(toBeAdded);

    tabs_.push_back(toBeAdded);

    lastTabEnd_ += toBeAdded->width_;

    if (!focusedTab_)
        focusedTab_ = toBeAdded;
}

void TabList::activate(Tab* toBeActivated)
{
    for (auto& it : tabs_)
        it->active_ = false;

    menus::clearFocus();
    setFocus(this, false);
    focusedTab_ = toBeActivated;
    
    toBeActivated->active_ = true;
    if (toBeActivated->activated_)
        *toBeActivated->activated_ = true;

    sound::playSound(sound::Tab);
}

