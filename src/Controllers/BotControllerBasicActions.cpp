#include "Controllers/BotController.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "Teams/Team.hpp"
#include "SpaceObjects/Home.hpp"
#include "System/randomizer.hpp"


void BotController::charge()
{
    Vector2f direction = ship()->location() - slave_->team()->home()->location();
    turnTo(direction + ship()->location());
    slaveFire(0);
    slaveUp(0);
    slaveDown(0);
    slaveBoost(0);
    switchWeapon();
    if (weaponChangeTimer_ > 0.5f)
        switchSpecial();
}

void BotController::land()
{
    moveTo(slave_->team()->home()->location(), 50.f, true, 0.f, true);
}

void BotController::switchWeapon()
{
    if (weaponChangeTimer_ <= 0.f)
    {
        slaveFire();
        slaveLeft();
        slaveFire();

        if (randomizer::random(0, 2) == 0)
            weaponChangeTimer_ = randomizer::random(20.f, 60.f);
        else
            weaponChangeTimer_ = randomizer::random(0.25f, 0.35f);
    }
}

void BotController::switchSpecial()
{
    if (specialChangeTimer_ <= 0.f)
    {
        slaveSpecial();
        slaveLeft();
        slaveSpecial();

        if (randomizer::random(0, 2) == 0)
            specialChangeTimer_ = randomizer::random(20.f, 60.f);
        else
            specialChangeTimer_ = randomizer::random(0.25f, 0.35f);
    }
}
