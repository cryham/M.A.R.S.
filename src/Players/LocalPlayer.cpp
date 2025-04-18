#include "Players/LocalPlayer.hpp"

#include "Controllers/controllers.hpp"
#include "System/settings.hpp"


LocalPlayer::LocalPlayer(controllers::ControlType controlType)
    : Player(controlType)
    , name_(controlType == controllers::cPlayer1 ? &settings::sPlayer1Name : &settings::sPlayer2Name)
    , color_(controlType == controllers::cPlayer1 ? &settings::clr1Player : &settings::clr2Player)
    , graphic_(controlType == controllers::cPlayer1 ? &settings::iPlayer1Ship : &settings::iPlayer2Ship)
{
    controller_ = controllers::addKeyController(this);
}
