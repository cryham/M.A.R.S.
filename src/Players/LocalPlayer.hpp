#pragma once

#include "Players/Player.hpp"

class Team;
class KeyController;


class LocalPlayer: public Player
{
    public:
        LocalPlayer(controllers::ControlType type);

        Color3f const&     color()   const {  return *color_;  }
        sf::String const&  name()    const {  return *name_;  }
        int                graphic() const {  return *graphic_;  }

        friend class Team;

    private:
        sf::String*  name_;
        Color3f* color_;
        int* graphic_;
        KeyController* controller_;
};
