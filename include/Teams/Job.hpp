#pragma once

#include "Controllers/controllers.hpp"
#include <map>


struct Job
{
    enum JobType
    {
        jLand, jCharge, jHeal, jUnfreeze, jAttackAny,
        jAttackTarget, jGetPUFuel, jGetPUHealth, jGetPUReverse,
        jGetPUShield, jGetPUSleep, jKickOutHome, jKickToEnemy,
        jWaitForBall, jProtectZone, jEscape, jGetControl
    };

    Job(JobType type, short priority, void* object = nullptr):
         type_(type),
         priority_(priority),
         object_(object)
    {   }

    JobType type_;
    short priority_;
    void* object_;


    bool operator< (Job const& rhs) const
    {
        return priority_ < rhs.priority_;
    }

    bool operator> (Job const& rhs) const
    {
        return priority_ > rhs.priority_;
    }
};

class BotController;

typedef std::multimap<Job, std::multimap<short, BotController*> > JobMap;
