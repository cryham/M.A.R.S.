#include "Interface/LabeledBox.hpp"

#include "Media/text.hpp"
#include "Interface/Label.hpp"

#include <SFML/OpenGL.hpp>


LabeledBox::LabeledBox (const sf::String& text, Vector2f const& topLeft, int width, int height)
    :UiElement(topLeft, width, height)
{
    if (!text.isEmpty())
    {
        label_ = new Label(text, TEXT_ALIGN_LEFT, Vector2f(5, 5),
            12.f, getColor3f(0.5f, 0.9f, 1.f), false);
        label_->setParent(this);
    }
}

LabeledBox::~LabeledBox ()
{
    if (label_)
        delete label_;
}

//  draw
void LabeledBox::draw() const
{
    UiElement::draw();

    Vector2f origin = getTopLeft();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
        // dark background
        if (isTopMost())   setColor4f(0.5,0.8,1.f, hoveredFadeTime_*0.05f);
        else               setColor4f(1.0f,1.0f,1.0f,0.f);
        glVertex2f(origin.x_, origin.y_);
        if (isTopMost())   setColor4f(0.5,0.8,1.f, 0.f);
        else               setColor4f(1.0f,1.0f,1.0f,0.f);
        glVertex2f(origin.x_, height_*0.7f + origin.y_);
        glVertex2f(width()*0.7f + origin.x_, height_*0.7f + origin.y_);
        glVertex2f(width()*0.7f + origin.x_, origin.y_);
    glEnd();

    glLineWidth(2.f);
    glBegin(GL_LINE_LOOP);
        // dark background
        if (isTopMost())   setColor4f(0.5,0.8,1.f, hoveredFadeTime_*0.15f+0.45f);
        else               setColor4f(1.0f,1.0f,1.0f,0.1f);
        glVertex2f(origin.x_, origin.y_);
        if (isTopMost())   setColor4f(0.5,0.8,1.f, 0.f);
        else               setColor4f(1.0f,1.0f,1.0f,0.f);
        glVertex2f(origin.x_, height_*0.7f + origin.y_);
        glVertex2f(width()*0.7f + origin.x_, height_*0.7f + origin.y_);
        glVertex2f(width()*0.7f + origin.x_, origin.y_);
    glEnd();

    if (label_)
        label_->draw();
}
