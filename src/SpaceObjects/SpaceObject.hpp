#pragma once

#include "System/Vector2f.hpp"
#include "Media/texture.hpp"
#include "physics.hpp"
#include "SpaceObjects/spaceObjects.hpp"

class Player;


class SpaceObject
{
    public:
        SpaceObject(spaceObjects::ObjectType type, Vector2f location, float radius, float mass)
            :location_(location)
            ,radius_(radius)
            ,mass_(mass)
            ,type_(type)
        {   }
        virtual ~SpaceObject()
        {   }

        virtual void update() = 0;
        virtual void draw() const = 0;

        virtual void onCollision(SpaceObject* source, Vector2f const& location,
                                 Vector2f const& direction, Vector2f const& velocity)
        {   }

        virtual void onShockWave(Player* damageSource, float intensity)
        {   }

        virtual void setDamageSource(Player* evilOne) {  damageSource_ = evilOne;  }
        Player*      damageSource() const             {  return damageSource_;  }

        spaceObjects::ObjectType type()     const {  return type_;  }
        Vector2f const&          location() const {  return location_;  }
        float                    radius()   const {  return radius_;  }
        float                    mass()     const {  return mass_;  }

        friend Vector2f  physics::attract(MobileSpaceObject*);
        friend void      physics::collide(MobileSpaceObject*, int);
        friend void      physics::overlap(MobileSpaceObject*, int);
        friend void      physics::causeShockWave(Player* damageSource, Vector2f const& location, float strength, float radius, float damage);

        //  utility
        #define  uv4(u,v)    glTexCoord2f( (u)*0.25f, (v)*0.25f)  // for tex with 4x4 tiles
        //#define  uv8 (u,v)  glTexCoord2f( (u)*0.125f, (v)*0.125f)   // old  128  particles.png
        #define  uv8(u,v)    glTexCoord2f( (u)*0.0625f, (v)*0.0625f)  // new  512  x2
        #define  uv8w(u,v)   glTexCoord2f( (u)*0.125f,  (v)*0.03125f)   // weapons.png  8x32

    protected:
        Vector2f location_;
        float radius_ = 1.f;
        float mass_ = 1.f;
        Player* damageSource_ = nullptr;

        //  new effects from weapons, factors fading out in time
        float chilled_ = 0.f;  // slows down movement, rotation
        float shocked_ = 0.f;  // paralyzed, disables weapons
    private:
        spaceObjects::ObjectType type_;
};
