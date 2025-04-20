#pragma once

#include "Hud/HudElement.hpp"
#include "System/Color3f.hpp"
#include "System/window.hpp"


class Message : public HudElement
{
    public:
        Message(sf::String const& message, Color3f const& color);

        void draw() const override;
        void update() override;;

        bool isDead() const;

    private:
        sf::String text_;
        Color3f    color_;
        Vector2f   location_;
        float      timer_;
        float      alpha_;
        float      speed_;
};

