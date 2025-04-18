#pragma once

#include "System/Vector2f.hpp"

class Player;
class Ship;


class CannonControl
{
    public:
        CannonControl(Vector2f const& location);

        void update();
        void draw() const;

        Player* getCarrier() const;
        Vector2f const& location() const;

    private:
        Vector2f respawnLocation_;
        Vector2f location_;
        Ship* ship_ = nullptr;
        bool collected_;
};
