#include "SpaceObjects/balls.hpp"

#include "SpaceObjects/Home.hpp"
#include "System/Vector2f.hpp"

#include <vector>


namespace balls
{
    namespace
    {
        std::vector<Ball*> balls_;
    }


    void addBall(float radius, Vector2f const& location)
    {
        // temporary list of all homes
        const auto& homes = spaceObjects::getHomes();

        if (homes.size() >= 2 && location == Vector2f(0,0))
        {
            Vector2f midPoint;
            for (const auto& it : homes)
                midPoint += it->location();
            midPoint /= homes.size();

            balls_.push_back(new Ball(midPoint, radius));
        }else
            balls_.push_back(new Ball(location, radius));
    }

    void update()
    {
        for (auto& ball : balls_)
            ball->update();
    }

    void draw()
    {
        for (auto& ball : balls_)
            ball->draw();
    }

    Ball* getBall()
    {
        return balls_.empty() ? nullptr : balls_[0];
    }

    void clear()
    {
        for (auto& ball : balls_)
            delete ball;
        balls_.clear();
    }
}
