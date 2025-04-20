#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"

#define TEXT_EDIT  0
#define PORT_EDIT  1
#define IP_EDIT    2


class TextEdit : public UiElement
{
    public:
        TextEdit (const sf::String& text, sf::String& value, const sf::String& fallBack,
            Vector2f const& topLeft, int width, int labelWidth, int type, int maxLength=0);
        ~TextEdit ();

        void mouseMoved(Vector2f const& position) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;
        void textEntered(sf::Uint32 keyCode) override;

        void draw() const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

    private:
        sf::String value_, fallBack_;
        Label* label_ = nullptr;
        unsigned maxLength_;
        unsigned cursorPos_;
        mutable int cursorTimer_;
        int type_;
        int labelWidth_;
};
