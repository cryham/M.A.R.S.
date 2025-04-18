#include "Interface/Line.hpp"

#include "Locales/locales.hpp"

#include <SFML/OpenGL.hpp>


Line::Line (Vector2f const& begin, Vector2f const& end)
    :UiElement(Vector2f(std::min(begin.x_, end.x_), std::min(begin.y_, end.y_)),
        std::abs(static_cast<int>(begin.x_ - end.x_)), std::abs(static_cast<int>(begin.y_ - end.y_)))
    ,begin_(begin)
    ,end_(end)
{   }

void Line::draw() const
{
    Vector2f begin = parent_->getTopLeft() + begin_;
    Vector2f end   = parent_->getTopLeft() + end_;

    if (!locales::getCurrentLocale().LTR_)
    {
        begin.x_ -= 2*begin_.x_;
        end.x_   -= 2*end_.x_;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glLineWidth(2.f);

    glBegin(GL_LINES);
        if (isTopMost())  setColor4f(0.5f, 0.8f, 1.0f, 1.0f);
        else              setColor4f(0.4f, 0.4f, 0.4f, 1.0f);
        glVertex2f(begin.x_,begin.y_);
        if (isTopMost())  setColor4f(0.5f, 0.8f, 1.0f, 0.0f);
        else              setColor4f(0.4f, 0.4f, 0.4f, 0.0f);
        glVertex2f(end.x_,end.y_);
    glEnd();
}
