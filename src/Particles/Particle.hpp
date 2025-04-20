#pragma once

#include "SpaceObjects/MobileSpaceObject.hpp"
#include "System/timer.hpp"

#include <list>


/// Base class for all particles.

template <typename Derived>
class Particle : public MobileSpaceObject
{
    public:
        /// Base ctor of a Particle.
        Particle(spaceObjects::ObjectType const& type, Vector2f const& location,
                float radius, float mass, float totalLifeTime)
            :MobileSpaceObject(type, location, radius, mass)
            ,totalLifeTime_(totalLifeTime)
            ,lifeTime_(0)
        {   }

        /// Calling this function will make the particle disappear in the next frame.
        /// Its life time is set equal to its total life time - therfore it will be deleted soon.
        void killMe()
        {
            lifeTime_ = totalLifeTime_;
        }

        /// Returns true, when the particle exist as long as it should.
        bool isDead()
        {
            return lifeTime_ >= totalLifeTime_;
        }

        static int count()
        {
            return Derived::activeParticles_.size();
        }

        static void clear()
        {
            for (auto& it : Derived::activeParticles_)
                delete it;
            Derived::activeParticles_.clear();
        }

        static void updateAll()
        {
            auto it = Derived::activeParticles_.begin();
            while (it != Derived::activeParticles_.end())
            {
                (*it)->update();
                if ((*it)->isDead())
                {
                    delete *it;
                    it = Derived::activeParticles_.erase(it);
                }else
                    ++it;
            }
        }

        static void drawAll()
        {
            for (auto& it : Derived::activeParticles_)
                it->draw();
        }

        static void spawn(Vector2f const& location,
            Vector2f const& direction, Vector2f const& sourcevel,
            Color3f const& color, Player* damageSource)
        {
            Derived::activeParticles_.push_back(new Derived(
                location, direction, sourcevel, color, damageSource));
        }

        static void collideWith(MobileSpaceObject* object)
        {
             // check for collision with each mobile object
            for (auto& it : Derived::activeParticles_)
            {
                // don't check for self collision
                if (it != object)
                {
                    // get faster object
                    MobileSpaceObject *source, *target;
                    if (object->velocity() > it->velocity())
                    {
                        source = object;
                        target = it;
                    }else
                    {   source = it;
                        target = object;
                    }

                    const float minDistSquared = std::pow(object->radius() + it->radius(), 2);
                    // if objects are moving
                    if (source->velocity().lengthSquare() > 0)
                    {
                        const Vector2f velSourceNorm = source->velocity().normalize();
                        const Vector2f velSourceOrtho(-velSourceNorm.y_, velSourceNorm.x_);
                        const Vector2f centerDist    = velSourceOrtho * ((source->location() - target->location())*velSourceOrtho);

                        // if path of object crosses target object
                        if (centerDist.lengthSquare() < minDistSquared)
                        {
                            const Vector2f lastFrameLocation = source->location() - source->velocity()*timer::frameTime()*0.6f;
                            const Vector2f chordMidPoint     = target->location() + centerDist;

                            // if path of object has intersected with target within the last frame
                            if ((source->location() - target->location()).lengthSquare() < minDistSquared ||
                                (lastFrameLocation - target->location()).lengthSquare() < minDistSquared ||
                                (chordMidPoint - source->location()) * (chordMidPoint - lastFrameLocation) < 0.f)
                            {
                                if (source->velocity() * (target->location() - lastFrameLocation) > 0)
                                {
                                    const Vector2f impactLocation  ((source->location() + target->location())*0.5f);
                                    const Vector2f impactDirection ((target->location() - source->location()).normalize());

                                    // calculate vel of objects in direction of impact before collision
                                    const Vector2f velSourceBefore = impactDirection * (source->velocity() * impactDirection);
                                    const Vector2f velTargetBefore = impactDirection * (target->velocity() * impactDirection);

                                    // calculate vel of objects in direction of impact after collision
                                    const Vector2f velSourceAfter =
                                        (velSourceBefore * source->mass() + velTargetBefore * target->mass() -
                                            (velSourceBefore - velTargetBefore)*target->mass())
                                        / (source->mass() + target->mass());
                                    const Vector2f velTargetAfter =
                                        (velSourceBefore * source->mass() + velTargetBefore * target->mass() -
                                            (velTargetBefore - velSourceBefore)*source->mass())
                                        / (source->mass() + target->mass());

                                    // calculate collision result
                                    target->onCollision(source, impactLocation, impactDirection, velSourceBefore);
                                    source->onCollision(target, impactLocation, impactDirection, velTargetBefore);

                                    // add to orthongonal speed component of initial vel
                                    // special case: Collision with rofle bullets is not physically correct, for improved gameplay
                                    if (source->type() == spaceObjects::oAmmoROFLE || target->type() == spaceObjects::oAmmoROFLE)
                                        target-> velocity() +=
                                            (0.05f * source->velocity()*source->mass() + (velTargetAfter - velTargetBefore) * 0.6);
                                    else
                                    if ((source->type() == spaceObjects::oAmmoRocket || target->type() == spaceObjects::oAmmoRocket) &&
                                        (source->type() != spaceObjects::oAmmoFist || target->type() != spaceObjects::oAmmoFist))
                                    {
                                        source->velocity() += (velSourceAfter - velSourceBefore) * 0.8;
                                        target->velocity() += (velTargetAfter - velTargetBefore) * 0.1;
                                    }else
                                    {   source->velocity() += (velSourceAfter - velSourceBefore) * 0.8;
                                        target->velocity() += (velTargetAfter - velTargetBefore) * 0.8;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    protected:
        /// Stores the targeted life time for ths particle.
        float totalLifeTime_;

        /// Stores the actual life time of the particle.
        float lifeTime_;
};
