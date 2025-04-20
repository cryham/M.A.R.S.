#include "SpaceObjects/asteroids.hpp"

#include "SpaceObjects/Asteroid.hpp"
#include "System/Vector2f.hpp"

#include <cstdlib>
#include <vector>


namespace asteroids
{
    namespace
    {
        std::vector<Asteroid*> asteroids_;
    }


    void addAsteroid(float radius, Vector2f const& location, int type)
    {
        asteroids_.push_back(new Asteroid(location, radius, type));
    }

    void update()
    {
        for (auto& ast : asteroids_)
            ast->update();
    }

    void draw()
    {
        for (auto& ast : asteroids_)
            ast->draw();
    }

    void clear()
    {
        for (auto& ast : asteroids_)
            delete ast;
        asteroids_.clear();
    }
}
