#include "Interface/RadioGroup.hpp"

#include "Menu/menus.hpp"


RadioGroup::RadioGroup ()
    :UiElement(Vector2f(), 0, 0)
{   }

RadioGroup::~RadioGroup()
{
    for (auto& it : radioButtons_)
        delete it;
}


void RadioGroup::mouseMoved(Vector2f const& position)
{
    for (auto& it : radioButtons_)
        it->mouseMoved(position);
}

void RadioGroup::mouseLeft(bool down)
{
    for (auto& it : radioButtons_)
        it->mouseLeft(down);
}

void RadioGroup::keyEvent(bool down, Key const& key)
{
    if (focusedButton_)
        focusedButton_->keyEvent(down, key);
}


bool RadioGroup::tabNext()
{
    if (radioButtons_.size() > 0)
    {
        if (focusedButton_)
        {
            int i(0);
            while (i < radioButtons_.size() && radioButtons_[i] != focusedButton_)
                ++i;
            ++i;

            if (i < radioButtons_.size())
            {
                menus::clearFocus();
                focusedButton_ = radioButtons_[i];
                focusedButton_->setFocus(focusedButton_, false);
                return false;
            }
        }else 
        {
            menus::clearFocus();
            focusedButton_ = radioButtons_[0];
            focusedButton_->setFocus(focusedButton_, false);
            return false;
        }
    }
    return true;
}

bool RadioGroup::tabPrevious()
{
   if (radioButtons_.size() > 0)
   {
        if (focusedButton_)
        {
            int i(radioButtons_.size()-1);
            while (i >= 0 && radioButtons_[i] != focusedButton_)
                --i;
            --i;

            if (i >= 0)
            {
                menus::clearFocus();
                focusedButton_ = radioButtons_[i];
                focusedButton_->setFocus(focusedButton_, false);
                return false;
            }
        }else
        {
            menus::clearFocus();
            focusedButton_ = radioButtons_[radioButtons_.size()-1];
            focusedButton_->setFocus(focusedButton_, false);
            return false;
        }
    }
    return true;
}


void RadioGroup::setFocus(UiElement* toBeFocused, bool isPrevious)
{
    UiElement::setFocus(this, isPrevious);
    RadioButton* toFocus = dynamic_cast<RadioButton*>(toBeFocused);
    if (toFocus)
        focusedButton_ = toFocus;
    else
    if (!focusedButton_)
    {
        if (isPrevious)
            tabPrevious();
        else
            tabNext();
    }
}

void RadioGroup::clearFocus()
{
    UiElement::clearFocus();
    focusedButton_ = nullptr;
    for (auto& it : radioButtons_)
        it->clearFocus();
}

void RadioGroup::draw () const
{
    for (const auto& it : radioButtons_)
        it->draw();
}

void RadioGroup::addRadioButton(RadioButton* toBeAdded)
{
    toBeAdded->setParent(this);
    radioButtons_.push_back(toBeAdded);
}

void RadioGroup::allOff()
{
    for (auto& it : radioButtons_)
        *(it->value_) = false;
}
