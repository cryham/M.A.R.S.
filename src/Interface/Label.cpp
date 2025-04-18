#include "Interface/Label.hpp"
#include "Media/text.hpp"

#include <SFML/OpenGL.hpp>


Label::Label (const sf::String& text, int textAlign,
        Vector2f const& topLeft, float fontSize, Color3f color, bool interactive, sf::Font* font)
    :UiElement(topLeft, 10, 10)
    ,text_(text)
    ,font_(font)
    ,textAlign_(textAlign)
    ,fontSize_(fontSize) //*scale_)
    ,color_(color)
    ,interactive_(interactive)
{   }

void Label::mouseMoved(Vector2f const& position)
{
    hovered_ = parent_->isHovered();
}

//  draw
void Label::draw() const
{
    UiElement::draw();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    Vector2f position(getTopLeft());
    if (interactive_)
    {
        if (parent_->isPressed())
            position += Vector2f(1, 1);
        
        float highlight(std::max(hoveredFadeTime_, focusedFadeTime_));
        Color3f color(color_*(1-highlight) +
            highlight*(Color3f(1.f, 0.8f, 0.9f) * (1-hoveredFadeTime_) +
            Color3f(1, 1, 1) * hoveredFadeTime_));
        
        if (parent_->isFocused())
        {
            sf::String tmp("[ " + text_ + " ]");
            text::drawScreenText(tmp, position, fontSize_, textAlign_, color, 1.f, font_);
        }else
            text::drawScreenText(text_, position, fontSize_, textAlign_, color, 1.f, font_);
    }else
        text::drawScreenText(text_, position, fontSize_, textAlign_, color_, 1.f, font_);
}

void Label::setFocus(UiElement* toBeFocused, bool isPrevious)
{
    focused_ = true;
}

void Label::clearFocus()
{
    focused_ = false;
}
