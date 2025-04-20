#include "Controllers/Controller.hpp"

// #include "Controllers/KeyController.hpp"
// #include "Controllers/BotController.hpp"
#include "Players/Player.hpp"
#include "Items/items.hpp"
#include "Weapons/Weapon.hpp"
#include "Specials/Special.hpp"


Controller::Controller(Player* slave):
    type_(slave->type()),
    slave_(slave)
{   }

void Controller::slaveUp (int up) const
{
    if (slave_->ship_->visible_ && !slave_->ship_->collectedPowerUps_[items::puSleep])
        slave_->ship_->up_ = up;
    else
        slave_->ship_->up_ = 0;
}

void Controller::slaveDown (int down) const
{
    if (slave_->ship_->visible_ && !slave_->ship_->collectedPowerUps_[items::puSleep])
        slave_->ship_->down_ = down;
    else
        slave_->ship_->down_ = 0;
}

void Controller::slaveBoost (int down) const
{
    if (slave_->ship_->visible_ && !slave_->ship_->collectedPowerUps_[items::puSleep])
        slave_->ship_->boost_ = down;
    else
        slave_->ship_->boost_ = 0;
}


void Controller::slaveLeft (int left) const
{
    if (!slave_->ship_->weaponChange_ && !slave_->ship_->specialChange_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep])
    {
        if (left && slave_->ship_->right_)
            slave_->ship_->right_ = 0;
        else
            slave_->ship_->left_ = left;
    }else
        slave_->ship_->left_ = 0;
}

void Controller::slaveRight (int right) const
{
    if (!slave_->ship_->weaponChange_ && !slave_->ship_->specialChange_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep])
    {
        if (right && slave_->ship_->left_)
            slave_->ship_->left_ = 0;
        else
            slave_->ship_->right_ = right;
    }else
        slave_->ship_->right_ = 0;
}

void Controller::slaveFire (int fire) const
{
    if (fire > 50 && !slave_->ship_->docked_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep] && slave_->ship_->frozen_<=0.f)
        slave_->ship_->weapon_->fire();
}

void Controller::slaveSpecial (int special) const
{
    if (special > 50 && !slave_->ship_->docked_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep] && slave_->ship_->frozen_<=0.f)
        slave_->ship_->special_->activate();
}

// single key presses
void Controller::slaveUp () const
{
}

void Controller::slaveDown () const
{
}

void Controller::slaveBoost () const
{
}


void Controller::slaveNext () const
{
    if (slave_->ship_->visible_ && !slave_->ship_->collectedPowerUps_[items::puSleep])
        slave_->ship_->WeaponNext();  //currentWeapon_->next();
    //     slave_->ship_->special_->next();  // todo: if boost
}

void Controller::slavePrev () const
{
    if (slave_->ship_->visible_ && !slave_->ship_->collectedPowerUps_[items::puSleep])
        slave_->ship_->WeaponPrev(); // currentWeapon_->previous();
    //     slave_->ship_->special_->previous();
}


void Controller::slaveLeft () const
{
    if (slave_->ship_->weaponChange_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep])
        slave_->ship_->WeaponPrev();  //currentWeapon_->previous();
    else
    if (slave_->ship_->specialChange_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep])
        slave_->ship_->special_->previous();
}

void Controller::slaveRight () const
{
    if (slave_->ship_->weaponChange_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep])
        slave_->ship_->WeaponNext();  //currentWeapon_->next();
    else
    if (slave_->ship_->specialChange_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep])
        slave_->ship_->special_->next();
}

void Controller::slaveFire () const
{
    if (slave_->ship_->docked_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep] && slave_->ship_->frozen_<=0.f)
    {
        slave_->ship_->weaponChange_ = !slave_->ship_->weaponChange_;
        slave_->ship_->specialChange_ = false;
    }
}

void Controller::slaveSpecial () const
{
    if (slave_->ship_->docked_ && slave_->ship_->visible_ &&
        !slave_->ship_->collectedPowerUps_[items::puSleep] && slave_->ship_->frozen_<=0.f)
    {
        slave_->ship_->specialChange_ = !slave_->ship_->specialChange_;
        slave_->ship_->weaponChange_ = false;
    }
}

Ship* Controller::ship() const
{
    return slave_->ship_;
}

controllers::ControlType Controller::type() const
{
    return type_;
}
