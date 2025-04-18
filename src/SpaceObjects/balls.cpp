#include "SpaceObjects/balls.hpp"

#include "SpaceObjects/Home.hpp"
#include "System/Vector2f.hpp"


namespace balls
{
    namespace
    {
        Ball* ball_ = nullptr;
    }


    void addBall(Vector2f const& location)
    {
        // temporary list of all homes
        const auto& homes = spaceObjects::getHomes();

        if (homes.size() >= 2 && location == Vector2f(0,0))
        {
            Vector2f midPoint;
            for (const auto& it : homes)
                midPoint += it->location();
            midPoint /= homes.size();

            ball_ = new Ball(midPoint);
        }else
            ball_ = new Ball(location);
    }

    void update()
    {
        if (ball_)
            ball_->update();
    }

    void draw()
    {
        if (ball_)
            ball_->draw();
    }

    Ball* getBall()
    {
        return ball_;
    }

    void clear()
    {
        if (ball_)
        {
            delete ball_;
            ball_ = nullptr;
        }
    }
}
