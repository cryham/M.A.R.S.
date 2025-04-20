#pragma once

#include "Interface/UiElement.hpp"

#include <vector>


class UiWindow : public UiElement
{
    public:
        UiWindow (int width, int height, Vector2f const& position = Vector2f());
        virtual ~UiWindow();

        void mouseMoved(Vector2f const& position) override;
        void mouseWheelMoved(Vector2f const& position, int delta) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;
        void textEntered(sf::Uint32 keyCode) override;

        bool tabNext() override;
        bool tabPrevious() override;

        virtual void draw () const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

        virtual void checkWidgets() = 0;
        virtual void onShow() = 0;

        void addWidget (UiElement* toBeAdded);

        void setTopMost(bool);
        bool isTopMost() const override {  return topMost_;  }
        bool isTabable() const override {  return false;  }

        virtual Vector2f getTopLeft() const  override;

    protected:
        std::vector<UiElement*> widgets_;
        UiElement* focusedWidget_ = nullptr;

    private:
        bool topMost_;
};
