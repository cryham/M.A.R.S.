#pragma once

#include "Hud/HudElement.hpp"

#include "Teams/Team.hpp"
#include "Players/Player.hpp"

#include <map>
#include <set>


class TabStats: public HudElement
{
    public:
        TabStats();

        void update() override;
        void draw() const override;

        void display(bool show = true);
        void refresh();

        bool visible() const;

    private:
        struct playerPtrCmp
        {
            bool operator()(Player* lhs, Player* rhs) const
            {
                return lhs->points_ > rhs->points_;
            }
        };
        struct teamPtrCmp
        {
            bool operator()(Team* lhs, Team* rhs) const
            {
                return lhs->points() > rhs->points();
            }
        };

        bool visible_, refresh_;
        int sumPoints_;
        std::multimap<Team*, std::multiset<Player*, playerPtrCmp>, teamPtrCmp > teamMap_;
};
