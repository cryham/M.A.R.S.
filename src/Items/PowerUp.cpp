#include "Items/PowerUp.hpp"

#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"


PowerUp::PowerUp(items::PowerUpType type, Vector2f const& location, float radius,
        float totalLifeTime, int texX, int texY, Color3f const& bgColor)
    :location_(location)
    ,radius_(radius)
    ,ships_()
    ,collected_(false)
    ,texX_(texX)
    ,texY_(texY)
    ,type_(type)
    ,lifeTime_(0.f)
    ,totalLifeTime_(totalLifeTime)
    ,bgColor_(bgColor)
{   }

PowerUp::~PowerUp()
{
    for (auto& it : ships_)
        it->collectedPowerUps_[type_] = nullptr;
}

void PowerUp::update()
{
    lifeTime_ += timer::frameTime();

    if (!collected_)
    {
        const auto& shipList = ships::getShips();
        for (const auto& it : shipList)
            if (it->getLife() > 0.f && (it->location() - location_).lengthSquare() < std::pow(radius_*2.f + it->radius(),2))
            {
                collected_ = true;
                if (type_ == items::puReverse || type_ == items::puSleep)
                {
                    for (const auto& ite : shipList)
                        if (it->getOwner()->team() != ite->getOwner()->team())
                            ships_.push_back(ite);
                }else
                    ships_.push_back(it);
            }
        
        auto it = ships_.begin();
        while (it != ships_.end())
        {
            if ((*it)->collectedPowerUps_[type_])
            {
                (*it)->collectedPowerUps_[type_]->lifeTime_ = 0;
                it = ships_.erase(it);
                lifeTime_ = totalLifeTime_;
            }else
            {
                (*it)->collectedPowerUps_[type_] = this;
                refreshLifeTime();
                ++it;
            }
        }

        if (lifeTime_ < M_PI/4.f)
            radius_ = std::sin(lifeTime_ * 2.f) * 15.f;
        else if (lifeTime_ > totalLifeTime_-0.38f)
            radius_ = -400.0*pow(lifeTime_+0.2-totalLifeTime_, 2)+25;
        else
            radius_ = 15.f;
    }else
    {
        auto it = ships_.begin();
        while (it != ships_.end())
        {
            if (*it && (*it)->getLife() == 0.f)
            {
                (*it)->collectedPowerUps_[type_] = nullptr;
                it = ships_.erase(it);
            }else
                ++it;
        }
        if (ships_.empty())
            lifeTime_ = totalLifeTime_;
    }
}

//  draw
void PowerUp::draw() const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glTranslatef(location_.x_, location_.y_, 0);

    bgColor_.gl4f(0.8f);
    glRotatef(fmod(timer::totalTime()*100.f, 360.f), 0.f, 0.f, 1.f);
    // glow
    glBegin(GL_QUADS);
        const int u1 = 0, v1 = 0;
        glTexCoord2f(u1*0.15625f,     v1*0.15625f);     glVertex2f(-radius_*2.f, -radius_*2.f);
        glTexCoord2f(u1*0.15625f,     (v1+1)*0.15625f); glVertex2f(-radius_*2.f, +radius_*2.f);
        glTexCoord2f((u1+1)*0.15625f, (v1+1)*0.15625f); glVertex2f(+radius_*2.f, +radius_*2.f);
        glTexCoord2f((u1+1)*0.15625f, v1*0.15625f);     glVertex2f(+radius_*2.f, -radius_*2.f);
    glEnd();

    glLoadIdentity();
    glTranslatef(location_.x_, location_.y_, 0);
    float scale(std::sin(timer::totalTime() *7.f) / 4.f + 1.f);
    glScalef(scale, scale, 1.f);
    glColor3f(1.f, 1.f, 1.f);
    // item layer
    glBegin(GL_QUADS);
        const int u2 = texX_, v2 = texY_;
        glTexCoord2f(u2*0.15625f,     v2*0.15625f);     glVertex2f(-radius_, -radius_);
        glTexCoord2f(u2*0.15625f,     (v2+1)*0.15625f); glVertex2f(-radius_, +radius_);
        glTexCoord2f((u2+1)*0.15625f, (v2+1)*0.15625f); glVertex2f(+radius_, +radius_);
        glTexCoord2f((u2+1)*0.15625f, v2*0.15625f);     glVertex2f(+radius_, -radius_);
    glEnd();

    glPopMatrix();
}

Vector2f const& PowerUp::location() const
{
    return location_;
}

float PowerUp::radius() const
{
    return radius_;
}

items::PowerUpType PowerUp::type() const
{
    return type_;
}

bool PowerUp::isDead() const
{
    return lifeTime_ >= totalLifeTime_;
}

bool PowerUp::isCollected() const
{
    return collected_;
}
