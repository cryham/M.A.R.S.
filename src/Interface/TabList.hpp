#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Tab.hpp"

#include <vector>


class TabList: public UiElement
{
    public:
        TabList (Vector2f const& topLeft, int width, int height);
        ~TabList();

        void mouseMoved(Vector2f const& position) override;
        void mouseWheelMoved(Vector2f const& position, int delta) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;
        void textEntered(sf::Uint32 keyCode) override;

        bool tabNext() override;
        bool tabPrevious() override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

        void draw() const override;

        void addTab(Tab* toBeAdded);
        void activate(Tab* toBeActivated);

    private:
        std::vector<Tab*> tabs_;
        Tab* focusedTab_ = nullptr;
        int lastTabEnd_;
};
