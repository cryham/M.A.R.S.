#include "SpaceObjects/Sun.hpp"

#include "Media/sound.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "System/timer.hpp"
#include "Particles/particles.hpp"
#include "System/randomizer.hpp"


Sun::Sun(Vector2f const& location, float radius, int type)
    :SpaceObject(spaceObjects::oSun, location, radius, radius * randomizer::random(40, 70))  // 50
    ,eruptionTimer_(0)
    ,type_(std::min(3, type))
{
    physics::addStaticObject(this);
    physics::addGravitySource(this);

    float r = randomizer::random(0.9f,1.f),
        g = randomizer::random(0.7f,1.f),
        b = std::min(g, randomizer::random(0.2f,1.f)),
        c = randomizer::random(0.3f,1.f);
    switch (type_)
    {
    case 0:  color_ = Color3f(1.f, g, b);  break;  // orange yellow
    case 1:  color_ = Color3f(b, g, 1.f);  break;  // white blue cyan
    case 2:  color_ = Color3f(c, b, 0.2f);  break;  // red brown
    case 3:  color_ = Color3f(g, std::min(r,g), 1.f);  break;  // white yellow
    }
}

void Sun::update()
{
    if (eruptionTimer_ > 0)
    {
        float time = timer::frameTime();
        eruptionTimer_ -= time;
    }else
    {
        // get random direction
        Vector2f dir = Vector2f::randDir();
        Vector2f pos = location_ + dir * radius_ * 0.9;
        float intensity = randomizer::random(0.5f, 2.0f);
        
        particles::spawnMultiple(intensity*5, particles::pEruption, pos, dir, dir*intensity);
        eruptionTimer_ = randomizer::random(1.0f, 2.5f);
    }
}

//  draw
void Sun::draw() const
{
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    auto tex = (texture::TextureType)(texture::Sun1 + type_);
    glBindTexture(GL_TEXTURE_2D, texture::getTexture(tex));

    color_.gl3f();

    float drawRadius = radius_*2;
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0);  glVertex2f(location_.x_-drawRadius, location_.y_-drawRadius);
        glTexCoord2i(0, 1);  glVertex2f(location_.x_-drawRadius, location_.y_+drawRadius);
        glTexCoord2i(1, 1);  glVertex2f(location_.x_+drawRadius, location_.y_+drawRadius);
        glTexCoord2i(1, 0);  glVertex2f(location_.x_+drawRadius, location_.y_-drawRadius);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Sun::onCollision(SpaceObject* with, Vector2f const& location,
                      Vector2f const& direction, Vector2f const& velocity)
{
    float strength = velocity.length();
    auto type = with->type();
    
    if (strength > 50 &&
        type != spaceObjects::oFuel &&
        type != spaceObjects::oAmmoBurner && type != spaceObjects::oAmmoFlamer2)
        particles::spawnMultiple(0.5, particles::pMud, location, direction, velocity, color_.brightened());

    if (type == spaceObjects::oShip ||
        type == spaceObjects::oBall && strength > 50)
    {
        Vector2f dir = location - location_;
        Vector2f pos = location_ + dir * 0.9;
        
        particles::spawnMultiple(strength * (0.1 + 0.1 * type_), particles::pEruption,
            pos, dir, dir*strength*0.00005, color_);
        eruptionTimer_ = randomizer::random(0.5f, 1.5f);
    }
}
