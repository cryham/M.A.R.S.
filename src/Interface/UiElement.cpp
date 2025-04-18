#include "Interface/UiElement.hpp"

#include "Media/sound.hpp"
#include "Menu/menus.hpp"
#include "System/timer.hpp"
#include "System/window.hpp"
#include "Locales/locales.hpp"

#include <GL/gl.h>
#include <SFML/OpenGL.hpp>
#include <iostream>


float UiElement::scale_ = 3.f/2.f;  // global UI scale


UiElement::UiElement(Vector2f const& topLeft, int width, int height)
    :topLeft_(topLeft * scale_)
    ,width_(width * scale_)
    ,height_(height * scale_)
    ,hovered_(false)
    ,focused_(false)
    ,pressed_(false)
    ,hoveredFadeTime_(0.f)
    ,focusedFadeTime_(0.f)
{   }


void UiElement::mouseMoved(Vector2f const& position)
{
    Vector2f topLeftAbs(getTopLeft());
    if (locales::getCurrentLocale().LTR_)
    {
        if (//(!sf::Mouse::isButtonPressed(sf::Mouse::Left) || pressed_) &&
            topLeftAbs.x_+width_ > position.x_ &&
            topLeftAbs.y_+height_ > position.y_ &&
            topLeftAbs.x_ < position.x_ &&
            topLeftAbs.y_ < position.y_)
            hovered_ = true;
        else
            hovered_ = false;
    }else
    {
        if (//(!sf::Mouse::isButtonPressed(sf::Mouse::Left) || pressed_) &&
            topLeftAbs.x_-width_ < position.x_ &&
            topLeftAbs.y_+height_ > position.y_ &&
            topLeftAbs.x_ > position.x_ &&
            topLeftAbs.y_ < position.y_)
            hovered_ = true;
        else
            hovered_ = false;
    }
}

void UiElement::mouseLeft(bool down)
{
    pressed_ = down && hovered_;
    if (isTabable() && down && hovered_)
    {
        menus::clearFocus();
        setFocus(this, false);
    }
}

//  draw
void UiElement::draw() const
{
    if      (hovered_)              hoveredFadeTime_ = 1.f;
    else if (hoveredFadeTime_ > 0)  hoveredFadeTime_ -= timer::realFrameTime()*5.f;
    if      (hoveredFadeTime_ < 0)  hoveredFadeTime_ = 0.f;
    if      (focused_)              focusedFadeTime_ = 1.f;
    else if (focusedFadeTime_ > 0)  focusedFadeTime_ -= timer::realFrameTime()*5.f;
    if      (focusedFadeTime_ < 0)  focusedFadeTime_ = 0.f;
}


void UiElement::setParent(UiElement* newParent)
{
    parent_ = newParent;
}

void UiElement::setFocus (UiElement* toBeFocused, bool isPrevious)
{
    if (parent_) parent_->setFocus(toBeFocused, isPrevious);
    focused_ = true;
}

void UiElement::clearFocus()
{
    focused_ = false;
}

Vector2f UiElement::getTopLeft() const
{
    Vector2f topLeft(topLeft_);
    if (!locales::getCurrentLocale().LTR_)
        topLeft.x_ *= -1.f;

    if (parent_)
        return topLeft + parent_->getTopLeft();
    else
        return topLeft;
}


int UiElement::width() const
{
    if (locales::getCurrentLocale().LTR_) return width_;
    else return -width_;
}


//  utility
void UiElement::setColor4f(float r, float g, float b, float a)
{
    glColor4f(r, g, b, a);  // cyan
    // glColor4f(b, g, r, a);  // pink
}

void UiElement::setColor3f(float r, float g, float b)
{
    glColor3f(r, g, b);  // cyan
    // glColor3f(b, g, r);  // pink
}

Color3f UiElement::getColor3f(float r, float g, float b)
{
    return Color3f(r, g, b);  // cyan
    // return Color3f(b, g, r);  // pink
}
