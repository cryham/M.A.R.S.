#include "TrailEffects/FloatingTrail.hpp"

#include "System/Vector2f.hpp"
#include "System/settings.hpp"
#include "System/timer.hpp"
#include "Media/texture.hpp"
#include "SpaceObjects/SpaceObject.hpp"

#include <SFML/OpenGL.hpp>


FloatingTrail::FloatingTrail(SpaceObject* target, float timeStep, float duration, float width, Color3f const& color):
    Trail(target),
    points_(duration/timeStep),
    frontIndex_(0),
    length_(0),
    timer_(0.f),
    timeStep_(timeStep),
    width_(width),
    color_(color)
{
    points_[frontIndex_++] = target_->location();
    ++length_;
}

void FloatingTrail::update()
{
    timer_ -= timer::frameTime();
    if (timer_ < 0.f)
    {   timer_ = timeStep_;
        if (target_)
        {
            points_[frontIndex_++] = target_->location();
            frontIndex_ %= points_.size();
            if (length_ < points_.size())
                ++length_;
        }
        else
            --length_;
    }
}

void FloatingTrail::draw() const
{
    if (length_ > 1)
    {
        const int u = 1, v = 1;

        Vector2f toNext;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Particles));
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBegin(GL_QUAD_STRIP);

        int lenMax = 100; //settings::C_resY * 3/4;
        bool oldMax = false, oldMax2 = false;

        for (int i = length_; i > 0; --i)
        {
            int index((frontIndex_-i + points_.size())%points_.size());

            float len = lenMax;
            if (i > 1)
            {
                int nextIndex((frontIndex_-i+1 + points_.size())%points_.size());
                Vector2f v = points_[nextIndex] - points_[index];
                len = v.length();
                if (len != 0.f)
                    toNext = v / len * width_;
            }

            if (!target_ && i==1 || len > lenMax || oldMax)
                color_.gl4f(0.f);
            else
                color_.gl4f(static_cast<float>(length_ - i)/length_);

            oldMax2 = oldMax;
            oldMax = len > lenMax;

            // if (len < lenMax)
            {
                uv8(u + 0.5,  v);    glVertex2f(points_[index].x_ + toNext.y_, points_[index].y_ - toNext.x_);
                uv8(u + 0.5,  v+1);  glVertex2f(points_[index].x_ - toNext.y_, points_[index].y_ + toNext.x_);
            }
        }

        if (target_)
        {
            color_.gl4f(0);
            uv8(u + frontIndex_%2, v);    glVertex2f(target_->location().x_ + toNext.y_, target_->location().y_ - toNext.x_);
            uv8(u + frontIndex_%2, v+1);  glVertex2f(target_->location().x_ - toNext.y_, target_->location().y_ + toNext.x_);
        }

        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

bool FloatingTrail::isDead() const
{
    return length_ <= 0;
}
